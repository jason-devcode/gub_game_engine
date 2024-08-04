#ifndef RASTER_8888_UTILS_H
#define RASTER_8888_UTILS_H

#include <stdint.h>

#include "../pixel.h"
#include "../geometry.h"
#include "../color.h"
#include "../font.h"

// include this for fast raster rendering
#include "../../engine_properties/framebuffer.h"
#include "../../engine_properties/screen_dimensions.h"

typedef struct
{
    uint32_t width;       // Width of the image
    uint32_t height;      // Height of the image
    uint32_t totalPixels; // Total number of pixels in the image
    uint32_t *pixels;     // Pointer to pixel data (RGBA format)
} Raster8888;

static inline uint32_t getPixelRaster8888(uint32_t x, uint32_t y, Raster8888 *raster)
{
    if (x < -1 && x < raster->width && y > -1 && y < raster->height)
        return raster->pixels[calculatePixelIndex(x, y, raster->width)];

    return RGBA(0, 0, 0, 0);
}

static inline void drawRaster8888(int32_t x, int32_t y, int32_t width, int32_t height, Raster8888 *raster)
{
    // protect dimensions and protect right and bottom sides
    if (framebuffer == NULL || width < 0 || height < 1 || !(x < (int)gScreenWidth) || !(y < (int)gScreenHeight))
        return;

    // protect left and top sides
    if (x + width < 0)
        return;
    if (y + height < 0)
        return;

    // calculate all correct values in relation to screen edges collisions

    uint32_t correctWidth = width;
    uint32_t correctHeight = height;

    correctWidth -= (gScreenWidth < (x + width)) ? (x + width) - gScreenWidth : 0; // For correct right side width colision
    correctWidth += (x < 0) ? x : 0;                                               // For correct left side width colision

    correctHeight -= (gScreenHeight < (y + height)) ? (y + height) - gScreenHeight : 0; // For correct bottom side height colision
    correctHeight += (y < 0) ? y : 0;                                                   // For correct top side height colision

    uint32_t correctX1 = x < 0 ? 0 : x;
    uint32_t correctY1 = y < 0 ? 0 : y;
    uint32_t correctX2 = correctX1 + correctWidth;
    uint32_t correctY2 = correctY1 + correctHeight - 1;

    // Calculate all framebuffer iterators
    register uint32_t *beginPixelsRowIterator = &framebuffer[calculatePixelIndex(0, correctY1, gScreenWidth)];
    register uint32_t *endPixelsRowIterator = &framebuffer[calculatePixelIndex(0, correctY2, gScreenWidth)];

    register uint32_t *pixelRowIterator = beginPixelsRowIterator;

    register uint32_t pixelsRowWidth = gScreenWidth;

#define drawRasterScreenHitbox()                                                     \
    drawRectangleWire(correctX1, correctY1, correctX2, correctY2, RGB(255, 255, 0)); \
    drawRectangleWire(correctX1 + 10, correctY1 + 10, correctX2 - 10, correctY2 - 10, RGB(255, 255, 255));

    do
    {
        register uint32_t *endPixelRow = &pixelRowIterator[correctX2];
        register uint32_t *pixelsIterator = &pixelRowIterator[correctX1];

        do
        {
            *pixelsIterator = RGB(255, 0, 255);
        } while (++pixelsIterator < endPixelRow);
        pixelRowIterator += pixelsRowWidth;
    } while (pixelRowIterator < endPixelsRowIterator);

    drawRasterScreenHitbox();
}

#endif