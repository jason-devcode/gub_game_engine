#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

#include "pixel.h"
#include "swap.h"
#include "fast_math.h"

/**
 * Draws a filled circle on the framebuffer with the specified color. The circle is
 * centered at (cx, cy) with a given radius and line weight. The function fills the
 * area between two concentric circles: one with the specified radius and another
 * with a reduced radius determined by the line weight.
 *
 * @param cx      The x-coordinate of the center of the circle.
 * @param cy      The y-coordinate of the center of the circle.
 * @param radius  The radius of the circle.
 * @param weight  The weight of the circle's outline, which affects the thickness of the circle.
 * @param color   The color to use for filling the circle, represented as a 32-bit unsigned integer.
 *
 * TODO: PENDING OPTIMIZE THIS
 */
void drawCircle(int cx, int cy, int radius, int weight, uint32_t color)
{
    register int correctRadius = radius + (weight >> 1) + 1;
    for (int Y = -radius; Y < radius; ++Y)
    {
        for (int X = -radius; X < radius; ++X)
        {
            register unsigned int distance = (X * X + Y * Y);
            register int innerRadius = radius - (weight + 1);
            register int outRadius = radius;

            register unsigned int squareOutRadius = outRadius * outRadius;
            register unsigned int squareInnerRadius = innerRadius * innerRadius;

            if (distance > squareInnerRadius && distance < squareOutRadius)
                pixel(X + cx, Y + cy, color);
        }
    }
}

/**
 * Draws a filled circle on the framebuffer with the specified color. The circle is
 * centered at (cx, cy) with a given radius. The function fills the circle by iterating
 * over a bounding box around the circle and checking if each point lies within the circle.
 *
 * @param cx      The x-coordinate of the center of the circle.
 * @param cy      The y-coordinate of the center of the circle.
 * @param radius  The radius of the circle.
 * @param color   The color to use for filling the circle, represented as a 32-bit unsigned integer.
 *
 * TODO: PENDING OPTIMIZE THIS
 */
void drawFilledCircle(int cx, int cy, int radius, uint32_t color)
{
    for (int Y = -radius; Y < radius; ++Y)
    {
        for (int X = -radius; X < radius; ++X)
        {
            if ((X * X + Y * Y) < radius * radius) // if the point is inside of the circle
            {
                pixel(X + cx, Y + cy, color);
            }
        }
    }
}

/**
 * Draws a line on the framebuffer from the starting point (x1, y1) to the ending
 * point (x2, y2) with the specified color. The function uses a line drawing algorithm
 * that determines the pixels along the line to be filled.
 *
 * @param x1      The x-coordinate of the starting point of the line.
 * @param y1      The y-coordinate of the starting point of the line.
 * @param x2      The x-coordinate of the ending point of the line.
 * @param y2      The y-coordinate of the ending point of the line.
 * @param color   The color to use for the line, represented as a 32-bit unsigned integer.
 */
static inline void drawLine(int x1, int y1, int x2, int y2, uint32_t color)
{
    register int DX = x2 - x1;
    register int DY = y2 - y1;

    register int absDX = fast_abs(DX);
    register int absDY = fast_abs(DY);

    register double steps = (double)(absDX > absDY ? absDX : absDY);
    steps += !steps; // protect for zero division

    register double stepX = (double)DX / steps;
    register double stepY = (double)DY / steps;

    register double x = x1;
    register double y = y1;
    --steps;
    do
    {
        pixel(x, y, color);
        x += stepX;
        y += stepY;
    } while (steps--);
}

/**
 * Draws a wireframe rectangle on the framebuffer with the specified color.
 * The rectangle is defined by the coordinates (x1, y1) for one corner and
 * (x2, y2) for the opposite corner. The function draws only the outline of the
 * rectangle by drawing lines between the corners.
 *
 * @param x1      The x-coordinate of one corner of the rectangle.
 * @param y1      The y-coordinate of one corner of the rectangle.
 * @param x2      The x-coordinate of the opposite corner of the rectangle.
 * @param y2      The y-coordinate of the opposite corner of the rectangle.
 * @param color   The color to use for the rectangle outline, represented as a 32-bit unsigned integer.
 */
static inline void drawRectangleWire(int x1, int y1, int x2, int y2, uint32_t color)
{
    fast_swap_bitwise(x1, x2);
    fast_swap_bitwise(y1, y2);

    drawLine(x1, y1, x2, y1, color);
    drawLine(x2, y1, x2, y2, color);
    drawLine(x2, y2, x1, y2, color);
    drawLine(x1, y2, x1, y1, color);
}

/**
 * Draws a filled rectangle on the framebuffer with the specified color.
 * The rectangle is defined by the coordinates (x1, y1) for the top-left corner
 * and (x2, y2) for the bottom-right corner. The function ensures the rectangle is
 * clipped to fit within the screen boundaries.
 *
 * @param x1      The x-coordinate of the top-left corner of the rectangle.
 * @param y1      The y-coordinate of the top-left corner of the rectangle.
 * @param x2      The x-coordinate of the bottom-right corner of the rectangle.
 * @param y2      The y-coordinate of the bottom-right corner of the rectangle.
 * @param color   The color to fill the rectangle with, represented as a 32-bit unsigned integer.
 */
static inline void drawRectangleFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
{
    // Normalize coordinates if necessary
    if (x1 > x2)
        fast_swap_bitwise(x1, x2);
    if (y1 > y2)
        fast_swap_bitwise(y1, y2);

    // Calculate width and height from normalized x1, y1, x2, y2
    int32_t width = x2 - x1 + 1;
    int32_t height = y2 - y1 + 1;

    // Protect against invalid dimensions and out-of-bounds issues
    if (framebuffer == NULL || width < 0 || height < 0 || !(x1 < (int)gScreenWidth) || !(y1 < (int)gScreenHeight))
        return;

    // Protect against drawing outside the left and top boundaries
    if (x2 < 0)
        return;
    if (y2 < 0)
        return;

    // Calculate correct values in relation to screen edges collisions
    uint32_t correctWidth = width;
    uint32_t correctHeight = height;

    correctWidth -= (gScreenWidth < (x2 + 1)) ? (x2 + 1) - gScreenWidth : 0; // Adjust for right edge collision
    correctWidth += (x1 < 0) ? x1 : 0;                                       // Adjust for left edge collision

    correctHeight -= (gScreenHeight < (y2 + 1)) ? (y2 + 1) - gScreenHeight : 0; // Adjust for bottom edge collision
    correctHeight += (y1 < 0) ? y1 : 0;                                         // Adjust for top edge collision

    uint32_t correctX1 = x1 < 0 ? 0 : x1;
    uint32_t correctY1 = y1 < 0 ? 0 : y1;
    uint32_t correctX2 = correctX1 + correctWidth - 1;
    uint32_t correctY2 = correctY1 + correctHeight - 1;

    // Calculate framebuffer iterators
    register uint32_t *beginPixelsRowIterator = &framebuffer[calculatePixelIndex(0, correctY1, gScreenWidth)];
    register uint32_t *endPixelsRowIterator = &framebuffer[calculatePixelIndex(0, correctY2, gScreenWidth)];

    register uint32_t *pixelRowIterator = beginPixelsRowIterator;

    register uint32_t pixelsRowWidth = gScreenWidth;

    do
    {
        register uint32_t *endPixelRow = &pixelRowIterator[correctX2 + 1];
        register uint32_t *pixelsIterator = &pixelRowIterator[correctX1];

        do
        {
            *pixelsIterator = color;
        } while (++pixelsIterator < endPixelRow);
        pixelRowIterator += pixelsRowWidth;
    } while (pixelRowIterator < endPixelsRowIterator);
}

#endif