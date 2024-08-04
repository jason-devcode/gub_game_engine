#ifndef IMAGE_FORMAT_BMP_UTILS_H
#define IMAGE_FORMAT_BMP_UTILS_H

#include <stdint.h> // For fixed-width integer types
#include <stdio.h>  // For file operations
#include <stdlib.h> // For memory allocation functions

#include "../raster.h" // For raster type

// BMP file header structure definition
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType;      // File type: must be 'BM'
    uint32_t bfSize;      // Size of the file in bytes
    uint16_t bfReserved1; // Reserved, must be zero
    uint16_t bfReserved2; // Reserved, must be zero
    uint32_t bfOffBits;   // Offset to start of pixel data
} BMPFileHeader;
#pragma pack(pop)

// BMP info header structure definition
#pragma pack(push, 1)
typedef struct
{
    uint32_t biSize;         // Size of the info header
    int32_t biWidth;         // Width of the image
    int32_t biHeight;        // Height of the image
    uint16_t biPlanes;       // Number of color planes
    uint16_t biBitCount;     // Number of bits per pixel
    uint32_t biCompression;  // Compression type
    uint32_t biSizeImage;    // Image size in bytes
    int32_t biXPelsPerMeter; // Pixels per meter in x-axis
    int32_t biYPelsPerMeter; // Pixels per meter in y-axis
    uint32_t biClrUsed;      // Number of colors used
    uint32_t biClrImportant; // Number of important colors
} BMPInfoHeader;
#pragma pack(pop)

/**
 * @brief Load a BMP image from a file.
 *
 * @param filename The path to the BMP file.
 * @return A pointer to the loaded Raster8888 structure, or NULL on failure.
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

    if (fileHeader.bfType != 0x4D42)
    {
        fclose(file);
        fprintf(stderr, "Not a BMP file\n");
        return NULL;
    }

    Raster8888 *raster = (Raster8888 *)malloc(sizeof(Raster8888));
    if (!raster)
    {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    raster->width = infoHeader.biWidth;
    raster->height = infoHeader.biHeight;
    raster->totalPixels = raster->width * raster->height;
    raster->pixels = (uint32_t *)malloc(raster->totalPixels * sizeof(uint32_t));
    if (!raster->pixels)
    {
        free(raster);
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    fseek(file, fileHeader.bfOffBits, SEEK_SET);
    fread(raster->pixels, sizeof(uint32_t), raster->totalPixels, file);

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
    infoHeader.biHeight = raster->height;
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
