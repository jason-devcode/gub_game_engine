#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

#include "pixel.h"
#include "swap.h"
#include "fast_math.h"
#include "color.h"
#include "pascal_triangle.h"
#include "analytic_geometry.h"
#include "vectorial_2D.h"

#define MAX_BEZIER_POINTS 100

// Global pointer to store the Pascal Triangle used for Bezier curve calculations
static int **gPascalTriangle = NULL;

/**
 * @brief Initializes geometric properties.
 *
 * This function allocates and initializes the Pascal Triangle with a size
 * of MAX_BEZIER_POINTS to be used in Bezier curve computations.
 */
static void initializeGeometryProps()
{
    gPascalTriangle = createPascalTriangle(MAX_BEZIER_POINTS);
}

/**
 * @brief Releases geometry-related resources.
 *
 * This function frees the memory allocated for the Pascal Triangle used in
 * Bezier curve computations, ensuring proper cleanup of resources.
 */
static void releaseGeometryResources()
{
    freePascalTriangle(gPascalTriangle, MAX_BEZIER_POINTS);
}

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
static inline void
drawHorizontalLine(int x1, int x2, int y, uint32_t color)
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
 * @brief Draws a line with depth testing, interpolating the z-coordinate along the line.
 *
 * This function draws a line from the coordinates (x1, y1, z1) to (x2, y2, z2) using the specified color.
 * The z-coordinate is linearly interpolated between the start and end points. The function performs
 * depth testing to ensure that only the closest pixel is drawn, preventing pixels that are farther away
 * from being rendered on top of closer pixels.
 *
 * @param x1 The x-coordinate of the start point.
 * @param y1 The y-coordinate of the start point.
 * @param z1 The z-coordinate of the start point.
 * @param x2 The x-coordinate of the end point.
 * @param y2 The y-coordinate of the end point.
 * @param z2 The z-coordinate of the end point.
 * @param color The color to draw the line with.
 */
static inline void drawLineDepthTest(int x1, int y1, double z1, int x2, int y2, double z2, uint32_t color)
{
    register int DX = x2 - x1;
    register int DY = y2 - y1;
    register double DZ = z2 - z1;

    register int absDX = fast_abs(DX);
    register int absDY = fast_abs(DY);

    register double steps = (double)(absDX > absDY ? absDX : absDY);
    steps += !steps; // protect for zero division

    register double stepX = (double)DX / steps;
    register double stepY = (double)DY / steps;
    register double stepZ = (double)DZ / steps;

    register double x = x1;
    register double y = y1;
    register double z = z1;
    --steps;
    do
    {
        pixelDepthTest(x, y, z, color);
        x += stepX;
        y += stepY;
        z += stepZ;
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

/**
 * @brief Draws the wireframe of a triangle with depth testing.
 *
 * This function draws the edges of a triangle defined by the vertices (x1, y1, z1),
 * (x2, y2, z2), and (x3, y3, z3) using the specified color. Each edge is drawn
 * with depth testing, ensuring that only the closest parts of the edges are visible
 * when rendered. The function leverages the `drawLineDepthTest` function to draw
 * each side of the triangle.
 *
 * @param x1 The x-coordinate of the first vertex.
 * @param y1 The y-coordinate of the first vertex.
 * @param z1 The z-coordinate of the first vertex.
 * @param x2 The x-coordinate of the second vertex.
 * @param y2 The y-coordinate of the second vertex.
 * @param z2 The z-coordinate of the second vertex.
 * @param x3 The x-coordinate of the third vertex.
 * @param y3 The y-coordinate of the third vertex.
 * @param z3 The z-coordinate of the third vertex.
 * @param color The color to draw the wireframe with.
 */
static inline void drawTriangleWireDepthTest(int x1, int y1, double z1, int x2, int y2, double z2, int x3, int y3, double z3, uint32_t color)
{
    drawLineDepthTest(x1, y1, z1, x2, y2, z2, color);
    drawLineDepthTest(x2, y2, z2, x3, y3, z3, color);
    drawLineDepthTest(x3, y3, z3, x1, y1, z1, color);
}

/**
 * @brief Draws a filled triangle with a gradient defined by three colors.
 *
 * Renders a filled triangle with vertices at (x1, y1), (x2, y2), and (x3, y3). The interior of the
 * triangle is filled with a gradient color determined by linearly interpolating the provided
 * colors `color1`, `color2`, and `color3` based on barycentric coordinates.
 *
 * @param x1 The x-coordinate of the first vertex.
 * @param y1 The y-coordinate of the first vertex.
 * @param x2 The x-coordinate of the second vertex.
 * @param y2 The y-coordinate of the second vertex.
 * @param x3 The x-coordinate of the third vertex.
 * @param y3 The y-coordinate of the third vertex.  

 * @param color1 The color at the first vertex.
 * @param color2 The color at the second vertex.
 * @param color3 The color at the third vertex.
 *
 * TODO: PENDING OPTIMIZE MORE
 */
static void drawFilledTriangleGradient(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color1, uint32_t color2, uint32_t color3)
{
    int minX = get_min_value_of_three(x1, x2, x3);
    int minY = get_min_value_of_three(y1, y2, y3);
    int maxX = get_max_value_of_three(x1, x2, x3);
    int maxY = get_max_value_of_three(y1, y2, y3);

    if (maxX < 0 || minX > gScreenWidth)
        return; // protect left and right screen side
    if (maxY < 0 || minY > gScreenHeight)
        return; // protect top and bottom screen side

    minX = get_max_value(minX, 0);             // cut rect left screen side
    maxX = get_min_value(gScreenWidth, maxX);  // cut rect left screen side
    minY = get_max_value(minY, 0);             // cut rect top screen side
    maxY = get_min_value(gScreenHeight, maxY); // cut rect bottom screen side

    register int tempTriangleArea = calculateTriangleAreaFromCoords(x1, y1, x2, y2, x3, y3);
    tempTriangleArea += !tempTriangleArea;
    register double invTriangleArea = 1.0 / tempTriangleArea;

    for (register int Y = minY; Y < maxY; ++Y)
    {
        for (register int X = minX; X < maxX; ++X)
        {
            register int areaAlpha = calculateTriangleAreaFromCoords(X, Y, x2, y2, x3, y3);
            register int areaBeta = calculateTriangleAreaFromCoords(x1, y1, X, Y, x3, y3);
            register int areaGamma = calculateTriangleAreaFromCoords(x1, y1, x2, y2, X, Y);

            if ((areaAlpha < 1 && areaBeta < 1 && areaGamma < 1) || (areaAlpha > -1 && areaBeta > -1 && areaGamma > -1))
            {
                register double alpha = (double)areaAlpha * invTriangleArea;
                register double beta = (double)areaBeta * invTriangleArea;
                register double gamma = (double)areaGamma * invTriangleArea;

                uint32_t color = triangularColorMix(color1, color2, color3, alpha, beta, gamma);
                pixel(X, Y, color);
            }
        }
    }
}

/**
 * @brief Mixes three values using the provided weights.
 *
 * This macro calculates a weighted sum of three values using the provided alpha, beta, and gamma weights.
 *
 * @param value1 The first value to be mixed.
 * @param value2 The second value to be mixed.
 * @param value3 The third value to be mixed.
 * @param alpha The weight for the first value.
 * @param beta The weight for the second value.
 * @param gamma The weight for the third value.
 *
 * @return The weighted sum of the three values.
 */
#define triangularValueMix(value1, value2, value3, alpha, beta, gamma) \
    ((double)(value1) * (alpha) + (double)(value2) * (beta) + (double)(value3) * (gamma))

/**
 * @brief Draws a filled triangle with a gradient defined by three colors.
 *
 * Renders a filled triangle with vertices at (x1, y1), (x2, y2), and (x3, y3). The interior of the
 * triangle is filled with a gradient color determined by linearly interpolating the provided
 * colors `color1`, `color2`, and `color3` based on barycentric coordinates. Also performs depth
 * testing to ensure correct rendering order.
 *
 * @param x1 The x-coordinate of the first vertex.
 * @param y1 The y-coordinate of the first vertex.
 * @param z1 The depth (z-coordinate) of the first vertex.
 * @param x2 The x-coordinate of the second vertex.
 * @param y2 The y-coordinate of the second vertex.
 * @param z2 The depth (z-coordinate) of the second vertex.
 * @param x3 The x-coordinate of the third vertex.
 * @param y3 The y-coordinate of the third vertex.
 * @param z3 The depth (z-coordinate) of the third vertex.
 * @param color1 The color at the first vertex.
 * @param color2 The color at the second vertex.
 * @param color3 The color at the third vertex.
 *
 * TODO: Optimize this function further for performance improvements.
 */
static void drawFilledTriangleGradientDepthTest(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, uint32_t color1, uint32_t color2, uint32_t color3)
{
    // Determine the bounding box of the triangle
    int minX = get_min_value_of_three(x1, x2, x3);
    int minY = get_min_value_of_three(y1, y2, y3);
    int maxX = get_max_value_of_three(x1, x2, x3);
    int maxY = get_max_value_of_three(y1, y2, y3);

    // Clip the bounding box to the screen dimensions
    if (maxX < 0 || minX > gScreenWidth)
        return; // Protect left and right screen sides
    if (maxY < 0 || minY > gScreenHeight)
        return; // Protect top and bottom screen sides

    minX = get_max_value(minX, 0);             // Cut rect left screen side
    maxX = get_min_value(gScreenWidth, maxX);  // Cut rect right screen side
    minY = get_max_value(minY, 0);             // Cut rect top screen side
    maxY = get_min_value(gScreenHeight, maxY); // Cut rect bottom screen side

    // Calculate the area of the triangle and its inverse for interpolation
    register int tempTriangleArea = calculateTriangleAreaFromCoords(x1, y1, x2, y2, x3, y3);
    tempTriangleArea += !tempTriangleArea; // Avoid division by zero
    register double invTriangleArea = 1.0 / tempTriangleArea;

    // drawTriangleWire(x1, y1, x2, y2, x3, y3, 0xFFFFFFFF);

    // Iterate over the bounding box
    for (register int Y = minY; Y < maxY; ++Y)
    {
        for (register int X = minX; X < maxX; ++X)
        {
            // Calculate the areas for barycentric coordinates
            register int areaAlpha = calculateTriangleAreaFromCoords(X, Y, x2, y2, x3, y3);
            register int areaBeta = calculateTriangleAreaFromCoords(x1, y1, X, Y, x3, y3);
            register int areaGamma = calculateTriangleAreaFromCoords(x1, y1, x2, y2, X, Y);

            // Check if the point (X, Y) is inside the triangle
            if ((areaAlpha < 0 && areaBeta < 0 && areaGamma < 0) || (areaAlpha > 0 && areaBeta > 0 && areaGamma > 0))
            {
                // Calculate barycentric coordinates
                register double alpha = (double)areaAlpha * invTriangleArea;
                register double beta = (double)areaBeta * invTriangleArea;
                register double gamma = (double)areaGamma * invTriangleArea;

                // Interpolate the color and depth value
                uint32_t color = triangularColorMix(color1, color2, color3, alpha, beta, gamma);
                double Z = triangularValueMix(z1, z2, z3, alpha, beta, gamma);

                // Set the pixel color if it passes the depth test
                pixelDepthTest(X, Y, Z, color);
            }
        }
    }
}

/**
 * @brief Draws a Bézier curve using an arbitrary number of control points.
 *
 * This function draws a Bézier curve defined by a set of control points.
 * It computes the curve by evaluating the Bernstein polynomials using the
 * Pascal triangle for the given control points.
 *
 * @param controlPoints Array of control points defining the Bézier curve.
 * @param numControlPoints Number of control points in the array.
 * @param numSteps Number of steps to interpolate the curve. Higher values
 *        result in a smoother curve.
 * @param color The color to use for drawing the Bézier curve.
 *
 * @note Before using this function, ensure that the geometry initializer
 *       has been called. This function relies on a precomputed Pascal
 *       triangle (`gPascalTriangle`), which must be initialized prior to
 *       calling `drawBezierNPoints`.
 */
static inline void drawBezierNPoints(const Vec2f *controlPoints, int numControlPoints, int numSteps, unsigned int color)
{
    float stepSize = 1.0f / numSteps;
    Vec2f currentPoint, previousPoint;

    for (int currentStep = 0; currentStep <= numSteps; ++currentStep)
    {
        float t = currentStep * stepSize;
        currentPoint = (Vec2f){0, 0};

        for (int controlPointIndex = 0; controlPointIndex < numControlPoints; ++controlPointIndex)
        {
            float bernsteinCoefficient = gPascalTriangle[numControlPoints - 1][controlPointIndex] *
                                         pow(t, controlPointIndex) *
                                         pow(1 - t, numControlPoints - 1 - controlPointIndex);

            currentPoint.x += bernsteinCoefficient * controlPoints[controlPointIndex].x;
            currentPoint.y += bernsteinCoefficient * controlPoints[controlPointIndex].y;
        }

        if (currentStep > 0)
            drawLine(previousPoint.x, previousPoint.y, currentPoint.x, currentPoint.y, color);
        previousPoint = currentPoint;
    }
}

#endif