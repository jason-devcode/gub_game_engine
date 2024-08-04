#ifndef RASTER_UTILS_H
#define RASTER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "pixel.h" // For pixel utilities

typedef struct
{
    uint32_t width;       // Width of the image
    uint32_t height;      // Height of the image
    uint32_t totalPixels; // Total number of pixels in the image
    uint8_t *pixels;      // Pointer to pixel data (1 bit per pixel)
} RasterMonochrome;

typedef struct
{
    uint32_t width;       // Width of the image
    uint32_t height;      // Height of the image
    uint32_t totalPixels; // Total number of pixels in the image
    uint8_t *pixels;      // Pointer to pixel data (1 byte per pixel)
} RasterGrayScale;

#include "raster/raster8888.h"

#endif