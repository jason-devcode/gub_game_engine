#ifndef IMAGE_FORMAT_TGA_UTILS_H
#define IMAGE_FORMAT_TGA_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TGA Header Structure
typedef struct
{
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;
    uint16_t colorMapStart;
    uint16_t colorMapLength;
    uint8_t colorMapDepth;
    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t pixelDepth;
    uint8_t imageDescriptor;
} TGAHeader;

#include "../raster.h" // Raster Structure for 32-bit RGBA

// Helper function to handle errors and clean up resources
static void handleError(const char *message, FILE *file, uint8_t *tempPixels, Raster8888 *raster)
{
    perror(message);
    if (tempPixels)
        free(tempPixels);
    if (raster)
    {
        if (raster->pixels)
            free(raster->pixels);
        free(raster);
    }
    if (file)
        fclose(file);
}

// Array of function pointers for different pixel data compression types
static int (*readPixelData[])(FILE *file, Raster8888 *raster) = {
    [2] = readUncompressedRGB, // Uncompressed RGB
    [10] = readCompressedRGB   // Compressed RGB
};

// Function to load TGA image
Raster8888 *loadTGA(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    TGAHeader header;
    if (fread(&header, sizeof(TGAHeader), 1, file) != 1)
    {
        handleError("Error reading TGA header", file, NULL, NULL);
        return NULL;
    }

    if (header.imageType != 2 && header.imageType != 10)
    { // Only supporting uncompressed RGB and RLE RGB
        handleError("Unsupported TGA image type", file, NULL, NULL);
        return NULL;
    }

    Raster8888 *raster = (Raster8888 *)malloc(sizeof(Raster8888));
    if (!raster)
    {
        handleError("Memory allocation failed", file, NULL, NULL);
        return NULL;
    }

    raster->width = header.width;
    raster->height = header.height;
    raster->totalPixels = raster->width * raster->height;
    raster->pixels = (uint32_t *)malloc(raster->totalPixels * sizeof(uint32_t));
    if (!raster->pixels)
    {
        handleError("Memory allocation failed", file, NULL, raster);
        return NULL;
    }

    int result = 0;
    if (header.imageType < sizeof(readPixelData) / sizeof(readPixelData[0]) && readPixelData[header.imageType])
    {
        result = readPixelData[header.imageType](file, raster);
    }
    else
    {
        handleError("Unsupported TGA image type", file, NULL, raster);
        return NULL;
    }

    if (result != 0)
    {
        handleError("Error reading TGA pixel data", file, NULL, raster);
        return NULL;
    }

    fclose(file);
    return raster;
}

// Function to read uncompressed RGB pixel data
static int readUncompressedRGB(FILE *file, Raster8888 *raster)
{
    size_t pixelDataSize = raster->totalPixels * 3;
    uint8_t *tempPixels = (uint8_t *)malloc(pixelDataSize);
    if (!tempPixels)
    {
        return -1;
    }

    if (fread(tempPixels, pixelDataSize, 1, file) != 1)
    {
        free(tempPixels);
        return -1;
    }

    for (size_t i = 0; i < raster->totalPixels; ++i)
    {
        uint8_t r = tempPixels[i * 3 + 0];
        uint8_t g = tempPixels[i * 3 + 1];
        uint8_t b = tempPixels[i * 3 + 2];
        raster->pixels[i] = (255 << 24) | (r << 16) | (g << 8) | b; // Set alpha to 255
    }

    free(tempPixels);
    return 0;
}

// Function to read compressed RGB pixel data (RLE)
static int readCompressedRGB(FILE *file, Raster8888 *raster)
{
    size_t pixelIndex = 0;
    while (pixelIndex < raster->totalPixels)
    {
        uint8_t headerByte;
        if (fread(&headerByte, sizeof(uint8_t), 1, file) != 1)
        {
            return -1;
        }

        bool isRLE = (headerByte & 0x80) != 0;
        uint8_t count = (headerByte & 0x7F) + 1;

        if (isRLE)
        {
            uint8_t rgb[3];
            if (fread(rgb, sizeof(uint8_t), 3, file) != 3)
            {
                return -1;
            }

            for (uint8_t i = 0; i < count; ++i)
            {
                if (pixelIndex >= raster->totalPixels)
                    break;
                raster->pixels[pixelIndex++] = (255 << 24) | (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
            }
        }
        else
        {
            uint8_t rgb[3 * 128]; // Max run length of 128
            if (fread(rgb, sizeof(uint8_t), 3 * count, file) != 3 * count)
            {
                return -1;
            }

            for (uint8_t i = 0; i < count; ++i)
            {
                if (pixelIndex >= raster->totalPixels)
                    break;
                raster->pixels[pixelIndex++] = (255 << 24) | (rgb[i * 3 + 0] << 16) | (rgb[i * 3 + 1] << 8) | rgb[i * 3 + 2];
            }
        }
    }

    return 0;
}

// Function to save Raster8888 as a TGA file
int saveTGA(const char *filename, const Raster8888 *raster)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    TGAHeader header = {0};
    header.idLength = 0;
    header.colorMapType = 0;
    header.imageType = 2; // Uncompressed RGB
    header.width = raster->width;
    header.height = raster->height;
    header.pixelDepth = 32; // 32 bits per pixel (RGBA)
    header.imageDescriptor = 0;

    if (fwrite(&header, sizeof(TGAHeader), 1, file) != 1)
    {
        fclose(file);
        fprintf(stderr, "Error writing TGA header\n");
        return -1;
    }

    size_t pixelDataSize = raster->totalPixels * sizeof(uint32_t);
    uint8_t *tempPixels = (uint8_t *)malloc(pixelDataSize);
    if (!tempPixels)
    {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    for (size_t i = 0; i < raster->totalPixels; ++i)
    {
        tempPixels[i * 4 + 0] = (raster->pixels[i] >> 16) & 0xFF; // Red
        tempPixels[i * 4 + 1] = (raster->pixels[i] >> 8) & 0xFF;  // Green
        tempPixels[i * 4 + 2] = raster->pixels[i] & 0xFF;         // Blue
        tempPixels[i * 4 + 3] = (raster->pixels[i] >> 24) & 0xFF; // Alpha
    }

    if (fwrite(tempPixels, pixelDataSize, 1, file) != 1)
    {
        free(tempPixels);
        fclose(file);
        fprintf(stderr, "Error writing TGA pixel data\n");
        return -1;
    }

    free(tempPixels);
    fclose(file);
    return 0;
}

// Function to free memory allocated for Raster8888
void freeRaster8888(Raster8888 *raster)
{
    if (raster)
    {
        if (raster->pixels)
            free(raster->pixels);
        free(raster);
    }
}

#endif // IMAGE_FORMAT_TGA_UTILS_H