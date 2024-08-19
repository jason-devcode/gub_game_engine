#ifndef IMAGE_FORMAT_BMP_UTILS_H
#define IMAGE_FORMAT_BMP_UTILS_H

#include <stdint.h> // For fixed-width integer types
#include <stdio.h>  // For file operations
#include <stdlib.h> // For memory allocation functions

#include "../raster.h" // For raster type

/**
 * @brief Constants for BMP bit depths and color masks.
 */
#define BMP_BIT_DEPTH_24 24       /**< 24 bits per pixel (RGB) */
#define BMP_BIT_DEPTH_32 32       /**< 32 bits per pixel (RGBA) */
#define BMP_ALPHA_MASK 0xFF000000 /**< Alpha mask for 32-bit RGBA pixels */
#define BMP_RED_SHIFT 16          /**< Shift value for red channel */
#define BMP_GREEN_SHIFT 8         /**< Shift value for green channel */
#define BMP_BLUE_SHIFT 0          /**< Shift value for blue channel */
#define BMP_ALPHA_SHIFT 24        /**< Shift value for alpha channel */

/**
 * @brief BMP file header structure.
 */
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType;      /**< File type identifier; must be 'BM' (0x4D42) */
    uint32_t bfSize;      /**< Size of the BMP file in bytes */
    uint16_t bfReserved1; /**< Reserved; must be zero */
    uint16_t bfReserved2; /**< Reserved; must be zero */
    uint32_t bfOffBits;   /**< Offset from the beginning of the file to the pixel data */
} BMPFileHeader;
#pragma pack(pop)

/**
 * @brief BMP info header structure.
 */
#pragma pack(push, 1)
typedef struct
{
    uint32_t biSize;         /**< Size of this header in bytes */
    int32_t biWidth;         /**< Width of the image in pixels */
    int32_t biHeight;        /**< Height of the image in pixels (can be negative for top-down bitmaps) */
    uint16_t biPlanes;       /**< Number of color planes (must be 1) */
    uint16_t biBitCount;     /**< Number of bits per pixel (e.g., 24 for RGB, 32 for RGBA) */
    uint32_t biCompression;  /**< Compression type (0 = uncompressed) */
    uint32_t biSizeImage;    /**< Size of the pixel data in bytes */
    int32_t biXPelsPerMeter; /**< Horizontal resolution (pixels per meter) */
    int32_t biYPelsPerMeter; /**< Vertical resolution (pixels per meter) */
    uint32_t biClrUsed;      /**< Number of colors used (0 = all colors) */
    uint32_t biClrImportant; /**< Number of important colors (0 = all colors) */
} BMPInfoHeader;
#pragma pack(pop)

/**
 * @brief Loads a BMP image from a file into a Raster8888 structure.
 *
 * This function supports both 24-bit and 32-bit BMP images. It handles both
 * top-down and bottom-up BMP formats and converts the image data into
 * 32-bit RGBA format, where each pixel is represented by a `uint32_t` value.
 *
 * @param filename The path to the BMP file to load.
 * @return A pointer to the loaded Raster8888 structure, or NULL if the file
 *         could not be loaded or the format is unsupported.
 */
Raster8888 *loadBMP(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // Check if the file is a BMP
    if (fileHeader.bfType != 0x4D42) // 'BM' in little-endian
    {
        fclose(file);
        fprintf(stderr, "Not a BMP file\n");
        return NULL;
    }

    // Check for supported bit depths
    if (infoHeader.biBitCount != BMP_BIT_DEPTH_24 && infoHeader.biBitCount != BMP_BIT_DEPTH_32)
    {
        fclose(file);
        fprintf(stderr, "Unsupported BMP bit depth: %d\n", infoHeader.biBitCount);
        return NULL;
    }

    // Allocate memory for the raster
    Raster8888 *raster = (Raster8888 *)malloc(sizeof(Raster8888));
    if (!raster)
    {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    raster->width = infoHeader.biWidth;
    raster->height = abs(infoHeader.biHeight); // Height can be negative
    raster->totalPixels = raster->width * raster->height;
    raster->pixels = (uint32_t *)malloc(raster->totalPixels * sizeof(uint32_t));
    if (!raster->pixels)
    {
        free(raster);
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Move the file pointer to the beginning of the pixel data
    fseek(file, fileHeader.bfOffBits, SEEK_SET);

    // Calculate the padded row size
    int row_padded = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;
    uint8_t *row = (uint8_t *)malloc(row_padded);

    if (!row)
    {
        free(raster->pixels);
        free(raster);
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Read the pixel data row by row
    for (int y = 0; y < raster->height; y++)
    {
        int row_index = (infoHeader.biHeight > 0) ? (raster->height - y - 1) : y; // Handle vertical orientation

        fread(row, 1, row_padded, file);

        for (int x = 0; x < raster->width; x++)
        {
            uint32_t pixel = 0;

            if (infoHeader.biBitCount == BMP_BIT_DEPTH_24)
            {
                // Convert 24-bit BMP to 32-bit RGBA
                pixel |= row[x * 3 + 2] << BMP_RED_SHIFT;   // Red
                pixel |= row[x * 3 + 1] << BMP_GREEN_SHIFT; // Green
                pixel |= row[x * 3 + BMP_BLUE_SHIFT];       // Blue
                pixel |= BMP_ALPHA_MASK;                    // Alpha (opaque)
            }
            else if (infoHeader.biBitCount == BMP_BIT_DEPTH_32)
            {
                // Read 32-bit BMP directly to 32-bit RGBA
                pixel |= row[x * 4 + 2] << BMP_RED_SHIFT;   // Red
                pixel |= row[x * 4 + 1] << BMP_GREEN_SHIFT; // Green
                pixel |= row[x * 4 + BMP_BLUE_SHIFT];       // Blue
                pixel |= row[x * 4 + 3] << BMP_ALPHA_SHIFT; // Alpha
            }

            raster->pixels[row_index * raster->width + x] = pixel;
        }
    }

    free(row);
    fclose(file);
    return raster;
}

/**
 * @brief Save a Raster8888 structure as a BMP file.
 *
 * @param filename The path to the BMP file to save.
 * @param raster A pointer to the Raster8888 structure to save.
 * @return 0 on success, or -1 on failure.
 */
int saveBMP(const char *filename, const Raster8888 *raster)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    BMPFileHeader fileHeader = {0};
    BMPInfoHeader infoHeader = {0};

    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + (raster->totalPixels * sizeof(uint32_t));
    fileHeader.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    infoHeader.biSize = sizeof(BMPInfoHeader);
    infoHeader.biWidth = raster->width;
    infoHeader.biHeight = -raster->height; // Negative height to vertical flip
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 32;   // Assuming 32 bits per pixel (RGBA)
    infoHeader.biCompression = 0; // No compression
    infoHeader.biSizeImage = raster->totalPixels * sizeof(uint32_t);

    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, file);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);
    fwrite(raster->pixels, sizeof(uint32_t), raster->totalPixels, file);

    fclose(file);
    return 0;
}

/**
 * @brief Free the memory allocated for a Raster8888 structure.
 *
 * @param raster A pointer to the Raster8888 structure to free.
 */
void freeRaster(Raster8888 *raster)
{
    if (raster)
    {
        if (raster->pixels)
        {
            free(raster->pixels);
        }
        free(raster);
    }
}

#endif
