#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

#include "pixel.h"
#include "swap.h"
#include "fast_math.h"

/**
 * @brief Draws a horizontal line on the framebuffer.
 *
 * This function draws a horizontal line from (x1, y) to (x2, y) with the specified color. The line will be clipped to the boundaries of the screen if necessary.
 *
 * @param x1 The starting x-coordinate of the line.
 * @param x2 The ending x-coordinate of the line.
 * @param y The y-coordinate of the line.
 * @param color The color of the line, represented as a 32-bit unsigned integer.
 */
static inline void drawHorizontalLine(int x1, int x2, int y, uint32_t color)
{
    if (y < 0)
        return; // protect up screen side

    if (gScreenHeight < y)
        return; // protect bottom screen side

    if (x1 > x2) // correct x order
        fast_swap_bitwise(x1, x2);

    if (gScreenWidth < x1)
        return; // protect right screen side

    if (x2 < 0)
        return; // protect left screen side

    // Correct values
    int correctX1 = x1 < 0 ? 0 : x1;
    int correctX2 = gScreenWidth < x2 ? gScreenWidth - 1 : x2;

    // Calculate framebuffer iterators
    register uint32_t *beginPixelsRowIterator = &framebuffer[calculatePixelIndex(correctX1, y, gScreenWidth)];
    register uint32_t *endPixelsRowIterator = &beginPixelsRowIterator[correctX2 - correctX1];

    register uint32_t *pixelsIterator = beginPixelsRowIterator;

    do
    {
        *pixelsIterator = color;
    } while (++pixelsIterator < endPixelsRowIterator);
}

/**
 * @brief Draws a vertical line on the framebuffer.
 *
 * This function draws a vertical line from (x, y1) to (x, y2) with the specified color. The line will be clipped to the boundaries of the screen if necessary.
 *
 * @param y1 The starting y-coordinate of the line.
 * @param y2 The ending y-coordinate of the line.
 * @param x The x-coordinate of the line.
 * @param color The color of the line, represented as a 32-bit unsigned integer.
 */
static inline void drawVerticalLine(int y1, int y2, int x, uint32_t color)
{
    if (x < 0)
        return; // protect left screen side

    if (gScreenWidth < x)
        return; // protect right screen side

    if (y1 > y2) // correct y order
        fast_swap_bitwise(y1, y2);

    if (gScreenHeight < y1)
        return; // protect bottom screen side

    if (y2 < 0)
        return; // protect up screen side

    // Correct values
    int correctY1 = y1 < 0 ? 0 : y1;
    int correctY2 = gScreenHeight < y2 ? gScreenHeight - 1 : y2;

    // Calculate framebuffer iterators
    register uint32_t *beginPixelsRowIterator = &framebuffer[calculatePixelIndex(x, correctY1, gScreenWidth)];
    register uint32_t *endPixelsRowIterator = &framebuffer[calculatePixelIndex(x, correctY2, gScreenWidth)];

    register uint32_t *pixelsIterator = beginPixelsRowIterator;

    do
    {
        *pixelsIterator = color;
    } while ((pixelsIterator += gScreenWidth) < endPixelsRowIterator);
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
 * @brief Global variables for storing current line coordinates.
 */
static int gCurrentLineToXCoord = 0;
static int gCurrentLineToYCoord = 0;

/**
 * @brief Sets the current line coordinates for subsequent line drawing.
 *
 * @param x The new x-coordinate.
 * @param y The new y-coordinate.
 */
#define setCurrentLineToCoords(x, y) \
    gCurrentLineToXCoord = x;        \
    gCurrentLineToYCoord = y;

/**
 * @brief Draws a line to the specified coordinates and updates current coordinates.
 *
 * @param nextX The x-coordinate of the next point.
 * @param nextY The y-coordinate of the next point.
 * @param color The color of the line.
 */
#define drawLineTo(nextX, nextY, color)                                        \
    drawLine(gCurrentLineToXCoord, gCurrentLineToYCoord, nextX, nextY, color); \
    setCurrentLineToCoords(nextX, nextY);

/**
 * @brief Draws the outline of a triangle (wireframe) on the screen.
 *
 * This function draws a wireframe triangle by connecting three specified vertices
 * using straight lines. Each vertex is defined by its (x, y) coordinates, and the
 * lines are drawn in the specified color.
 *
 * @param x1 The x-coordinate of the first vertex.
 * @param y1 The y-coordinate of the first vertex.
 * @param x2 The x-coordinate of the second vertex.
 * @param y2 The y-coordinate of the second vertex.
 * @param x3 The x-coordinate of the third vertex.
 * @param y3 The y-coordinate of the third vertex.
 * @param color The color of the triangle outline.
 */
static inline void drawTriangleWire(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x3, y3, color);
    drawLine(x3, y3, x1, y1, color);
}

#endif