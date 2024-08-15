#ifndef CARTESIAN_2D_SPACE_UTILS_H
#define CARTESIAN_2D_SPACE_UTILS_H

#include "../core/engine_properties/screen_dimensions.h"
#include "geometry.h"
#include "font.h"

/**
 * @brief Maximum value for the x-axis in the Cartesian coordinate system.
 */
static int gCartesianMaxXAxisValue = 8;

/**
 * @brief Maximum value for the y-axis in the Cartesian coordinate system.
 */
static int gCartesianMaxYAxisValue = 8;

/**
 * @brief Initializes the Cartesian coordinate system utilities.
 *
 * This function sets up the necessary parameters for working with the Cartesian coordinate system.
 * It calculates the required parameters based on the current screen dimensions.
 */
static inline void initializeCartesian2DSpaceUtils(int maxXAxisValue, int maxYAxisValue)
{
    gCartesianMaxXAxisValue = maxXAxisValue;
    gCartesianMaxYAxisValue = maxYAxisValue;
}

/**
 * @brief Draws the x-axis lines and labels on the screen.
 *
 * This macro draws vertical grid lines representing the x-axis of a Cartesian coordinate system on the screen.
 * It also labels the x-axis values at regular intervals.
 *
 * @param colorLines The color of the grid lines.
 * @param colorText The color of the text labels.
 */
#define drawXAxis(colorLines, colorText)                                               \
    register int DX = gScreenWidth / (gCartesianMaxXAxisValue << 1);                   \
    register int x = DX;                                                               \
    do                                                                                 \
    {                                                                                  \
        drawVerticalLine(0, gScreenHeight, x, GRAY_900);                               \
        drawVerticalLine(gHalfScreenHeight - 5, gHalfScreenHeight + 5, x, colorLines); \
    } while ((x += DX) < gScreenWidth);                                                \
    x = DX;                                                                            \
    register int valueXAxis = -(gCartesianMaxXAxisValue - 1);                          \
    do                                                                                 \
    {                                                                                  \
        drawFormattedText(x + 4, gHalfScreenHeight + 8, colorText, "%d", valueXAxis);  \
        ++valueXAxis;                                                                  \
    } while ((x += DX) < gScreenWidth);

/**
 * @brief Draws the y-axis lines and labels on the screen.
 *
 * This macro draws horizontal grid lines representing the y-axis of a Cartesian coordinate system on the screen.
 * It also labels the y-axis values at regular intervals.
 *
 * @param colorLines The color of the grid lines.
 * @param colorText The color of the text labels.
 */
#define drawYAxis(colorLines, colorText)                                                \
    register int DY = gScreenHeight / (gCartesianMaxYAxisValue << 1);                   \
    register int y = DY;                                                                \
    do                                                                                  \
    {                                                                                   \
        drawHorizontalLine(0, gScreenWidth, y, GRAY_900);                               \
        drawHorizontalLine(gHalfScreenWidth - 5, gHalfScreenWidth + 5, y, colorLines);  \
    } while ((y += DY) < gScreenHeight);                                                \
    y = DY;                                                                             \
    register int valueYAxis = (gCartesianMaxYAxisValue - 1);                            \
    do                                                                                  \
    {                                                                                   \
        drawFormattedText(gHalfScreenHeight + 16, y - 10, colorText, "%d", valueYAxis); \
        --valueYAxis;                                                                   \
    } while ((y += DY) < gScreenHeight);

/**
 * @brief Draws the Cartesian coordinate plane on the screen.
 *
 * This function draws both the x-axis and y-axis of a Cartesian coordinate system on the screen.
 * It uses predefined colors for the lines and labels.
 */
static inline void drawScreenCartesianPlane()
{
#define LINE_COLOR SLATE_400
    drawXAxis(LINE_COLOR, GREEN_900);
    drawYAxis(LINE_COLOR, GREEN_900);

    drawHorizontalLine(0, gScreenWidth, gHalfScreenHeight, LINE_COLOR);
    drawVerticalLine(0, gScreenHeight, gHalfScreenWidth, LINE_COLOR);
}

/**
 * @brief Converts a screen x-coordinate to a Cartesian 2D x-coordinate.
 *
 * @param x The screen x-coordinate.
 * @return The corresponding Cartesian 2D x-coordinate.
 */
#define convertScreenXToCartesian2DX(x) \
    ((double)(int)(((int)(x) - (gHalfScreenWidth)) * gCartesianMaxXAxisValue) / (double)gHalfScreenWidth)

/**
 * @brief Converts a screen y-coordinate to a Cartesian 2D y-coordinate.
 *
 * @param y The screen y-coordinate.
 * @return The corresponding Cartesian 2D y-coordinate.
 */
#define convertScreenYToCartesian2DY(y) \
    ((double)(int)(-((int)(y) - (gHalfScreenHeight)) * gCartesianMaxYAxisValue) / (double)gHalfScreenHeight)

/**
 * @brief Converts a Cartesian 2D x-coordinate to a screen x-coordinate.
 *
 * @param x The Cartesian 2D x-coordinate.
 * @return The corresponding screen x-coordinate.
 */
#define convertCartesian2DXToScreenX(x) \
    (gHalfScreenWidth + (((x) * gScreenWidth) / (gCartesianMaxXAxisValue << 1)))

/**
 * @brief Converts a Cartesian 2D y-coordinate to a screen y-coordinate.
 *
 * @param y The Cartesian 2D y-coordinate.
 * @return The corresponding screen y-coordinate.
 */
#define convertCartesian2DYToScreenY(y) \
    (gHalfScreenHeight - (((y) * gScreenHeight) / (gCartesianMaxYAxisValue << 1)))

/**
 * @brief Draws a pixel at the specified Cartesian 2D coordinates.
 *
 * @param x The Cartesian 2D x-coordinate.
 * @param y The Cartesian 2D y-coordinate.
 * @param color The color of the pixel.
 */
#define pixelCartesian2D(x, y, color) \
    pixel(convertCartesian2DXToScreenX(x), convertCartesian2DYToScreenY(y), color);

/**
 * @brief Sets the current line drawing position to the specified Cartesian 2D coordinates.
 *
 * @param x The Cartesian 2D x-coordinate.
 * @param y The Cartesian 2D y-coordinate.
 */
#define setCurrentLineToCoordsCartesian2D(x, y) \
    setCurrentLineToCoords(convertCartesian2DXToScreenX(x), convertCartesian2DYToScreenY(y));

/**
 * @brief Draws a line to the specified Cartesian 2D coordinates.
 *
 * @param x The Cartesian 2D x-coordinate of the end point.
 * @param y The Cartesian 2D y-coordinate of the end point.
 * @param color The color of the line.
 */
#define drawLineToCartesian2DCoords(x, y, color) \
    drawLineTo(convertCartesian2DXToScreenX(x), convertCartesian2DYToScreenY(y), color);

/**
 * @brief Draws a filled circle at the specified Cartesian 2D coordinates.
 *
 * @param cx The Cartesian 2D x-coordinate of the circle center.
 * @param cy The Cartesian 2D y-coordinate of the circle center.
 * @param radius The radius of the circle.
 * @param color The color of the circle.
 */
#define drawCircleFillCartesian2D(cx, cy, radius, color) \
    drawFilledCircle(convertCartesian2DXToScreenX(cx), convertCartesian2DYToScreenY(cy), radius, color);

/**
 * @brief Draws a wireframe parallelogram at the specified Cartesian 2D coordinates.
 *
 * @param x1 The Cartesian 2D x-coordinate of the first vertex.
 * @param y1 The Cartesian 2D y-coordinate of the first vertex.
 * @param x2 The Cartesian 2D x-coordinate of the second vertex.
 * @param y2 The Cartesian 2D y-coordinate of the second vertex.
 * @param color The color of the parallelogram.
 */
#define drawParallelogramWireCartesian2D(x1, y1, x2, y2, color)                                                                                                        \
    drawLine(convertCartesian2DXToScreenX(0), convertCartesian2DYToScreenY(0), convertCartesian2DXToScreenX(x1), convertCartesian2DYToScreenY(y1), color);             \
    drawLine(convertCartesian2DXToScreenX(0), convertCartesian2DYToScreenY(0), convertCartesian2DXToScreenX(x2), convertCartesian2DYToScreenY(y2), color);             \
    drawLine(convertCartesian2DXToScreenX(x1), convertCartesian2DYToScreenY(y1), convertCartesian2DXToScreenX(x1 + x2), convertCartesian2DYToScreenY(y1 + y2), color); \
    drawLine(convertCartesian2DXToScreenX(x2), convertCartesian2DYToScreenY(y2), convertCartesian2DXToScreenX(x1 + x2), convertCartesian2DYToScreenY(y1 + y2), color);

#endif // CARTESIAN_2D_SPACE_UTILS_H