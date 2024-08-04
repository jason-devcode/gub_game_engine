#ifndef PORTABLE_BITMAP_UTILS
#define PORTABLE_BITMAP_UTILS

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../raster.h" // For raster structures

/**
 * @brief Header for PBM (Portable BitMap) files.
 */
typedef struct
{
    uint16_t magicNumber; // P1 for ASCII version - P4 for binary version
    uint32_t imageWidth;  // Width of the image
    uint32_t imageHeight; // Height of the image
} PBMHeader;

/**
 * @brief Header for PGM (Portable GrayMap) files.
 */
typedef struct
{
    uint16_t magicNumber; // P2 for ASCII version - P5 for binary version
    uint32_t imageWidth;  // Width of the image
    uint32_t imageHeight; // Height of the image
    uint8_t maxGrey;      // Maximum gray value
} PGMHeader;

/**
 * @brief Header for PPM (Portable PixMap) files.
 */
typedef struct
{
    uint16_t magicNumber; // P3 for ASCII version - P6 for binary version
    uint32_t imageWidth;  // Width of the image
    uint32_t imageHeight; // Height of the image
    uint8_t maxColor;     // Maximum color value
} PPMHeader;

/**
 * @brief Load a PBM image from a file.
 *
 * @param filename The path to the PBM file.
 * @return A pointer to the loaded RasterMonochrome structure, or NULL on failure.
 */
static inline RasterMonochrome *loadPBM(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    PBMHeader header;
    if (fread(&header, sizeof(PBMHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error reading PBM header\n");
        return NULL;
    }

    RasterMonochrome *raster = (RasterMonochrome *)malloc(sizeof(RasterMonochrome));
    if (!raster)
    {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    raster->width = header.imageWidth;
    raster->height = header.imageHeight;
    raster->totalPixels = (raster->width * raster->height + 7) / 8; // Calculating total bytes
    raster->pixels = (uint8_t *)malloc(raster->totalPixels);
    if (!raster->pixels)
    {
        free(raster);
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    if (fread(raster->pixels, raster->totalPixels, 1, file) != 1)
    {
        free(raster->pixels);
        free(raster);
        fclose(file);
        fprintf(stderr, "Error reading PBM pixel data\n");
        return NULL;
    }

    fclose(file);
    return raster;
}

/**
 * @brief Save a RasterMonochrome structure as a PBM file.
 *
 * @param filename The path to the PBM file to save.
 * @param raster A pointer to the RasterMonochrome structure to save.
 * @return 0 on success, or -1 on failure.
 */
static inline int savePBM(const char *filename, const RasterMonochrome *raster)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    PBMHeader header = {0x5034, raster->width, raster->height}; // P4 magic number
    if (fwrite(&header, sizeof(PBMHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing PBM header\n");
        return -1;
    }

    if (fwrite(raster->pixels, raster->totalPixels, 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing PBM pixel data\n");
        return -1;
    }

    fclose(file);
    return 0;
}

/**
 * @brief Free the memory allocated for a RasterMonochrome structure.
 *
 * @param raster A pointer to the RasterMonochrome structure to free.
 */
static inline void freeRasterMonochrome(RasterMonochrome *raster)
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

/**
 * @brief Load a PGM image from a file.
 *
 * @param filename The path to the PGM file.
 * @return A pointer to the loaded RasterGrayScale structure, or NULL on failure.
 */
static inline RasterGrayScale *loadPGM(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    PGMHeader header;
    if (fread(&header, sizeof(PGMHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error reading PGM header\n");
        return NULL;
    }

    RasterGrayScale *raster = (RasterGrayScale *)malloc(sizeof(RasterGrayScale));
    if (!raster)
    {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    raster->width = header.imageWidth;
    raster->height = header.imageHeight;
    raster->totalPixels = raster->width * raster->height;
    raster->pixels = (uint8_t *)malloc(raster->totalPixels);
    if (!raster->pixels)
    {
        free(raster);
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    if (fread(raster->pixels, raster->totalPixels, 1, file) != 1)
    {
        free(raster->pixels);
        free(raster);
        fclose(file);
        fprintf(stderr, "Error reading PGM pixel data\n");
        return NULL;
    }

    fclose(file);
    return raster;
}

/**
 * @brief Save a RasterGrayScale structure as a PGM file.
 *
 * @param filename The path to the PGM file to save.
 * @param raster A pointer to the RasterGrayScale structure to save.
 * @return 0 on success, or -1 on failure.
 */
static inline int savePGM(const char *filename, const RasterGrayScale *raster)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    PGMHeader header = {0x5035, raster->width, raster->height, 255}; // P5 magic number, maxGrey 255
    if (fwrite(&header, sizeof(PGMHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing PGM header\n");
        return -1;
    }

    if (fwrite(raster->pixels, raster->totalPixels, 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing PGM pixel data\n");
        return -1;
    }

    fclose(file);
    return 0;
}

/**
 * @brief Free the memory allocated for a RasterGrayScale structure.
 *
 * @param raster A pointer to the RasterGrayScale structure to free.
 */
static inline void freeRasterGrayScale(RasterGrayScale *raster)
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

/**
 * @brief Load a PPM image from a file.
 *
 * @param filename The path to the PPM file.
 * @return A pointer to the loaded Raster8888 structure, or NULL on failure.
 */
static inline Raster8888 *loadPPM(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    PPMHeader header;
    if (fread(&header, sizeof(PPMHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error reading PPM header\n");
        return NULL;
    }

    Raster8888 *raster = (Raster8888 *)malloc(sizeof(Raster8888));
    if (!raster)
    {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    raster->width = header.imageWidth;
    raster->height = header.imageHeight;
    raster->totalPixels = raster->width * raster->height;
    raster->pixels = (uint32_t *)malloc(raster->totalPixels * 3); // 3 bytes per pixel
    if (!raster->pixels)
    {
        free(raster);
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    if (fread(raster->pixels, raster->totalPixels * 3, 1, file) != 1)
    {
        free(raster->pixels);
        free(raster);
        fclose(file);
        fprintf(stderr, "Error reading PPM pixel data\n");
        return NULL;
    }

    fclose(file);
    return raster;
}

/**
 * @brief Save a Raster8888 structure as a PPM file.
 *
 * @param filename The path to the PPM file to save.
 * @param raster A pointer to the Raster8888 structure to save.
 * @return 0 on success, or -1 on failure.
 */
static inline int savePPM(const char *filename, const Raster8888 *raster)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    PPMHeader header = {0x5036, raster->width, raster->height, 255}; // P6 magic number, maxColor 255
    if (fwrite(&header, sizeof(PPMHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing PPM header\n");
        return -1;
    }

    if (fwrite(raster->pixels, raster->totalPixels * 3, 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing PPM pixel data\n");
        return -1;
    }

    fclose(file);
    return 0;
}
/**
 * @brief Free the memory allocated for a Raster8888 structure.
 *
 * @param raster A pointer to the Raster8888 structure to free.
 */
static inline void freeRaster8888(Raster8888 *raster)
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

#endif // PORTABLE_BITMAP_UTILS