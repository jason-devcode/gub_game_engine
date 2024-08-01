/**
 * @file font.h
 * @brief Header file for font rendering functions.
 *
 * This file provides functionality to render characters and text using a bitmap font. It includes
 * functions to draw individual characters and formatted text at specified positions with a given color.
 */

#ifndef FONT
#define FONT

#include <stdarg.h>  ///< For variable argument lists.
#include <string.h>  ///< For string manipulation functions.
#include <stdio.h>   ///< For standard I/O functions.
#include <stdbool.h> ///< For boolean type.

#include "font_data.h"                               ///< Font bitmap data.
#include "../prototypes/graphic_engine_prototypes.h" ///< Graphics engine prototypes for pixel drawing functions.

/**
 * @brief Draw a single character at a specified position.
 *
 * This function renders a character using the provided bitmap font data. The character is drawn
 * at the (x, y) coordinates with the specified color. Each character is represented as an 8x8
 * bitmap.
 *
 * @param x The x-coordinate of the position where the character should be drawn.
 * @param y The y-coordinate of the position where the character should be drawn.
 * @param asciiCode The ASCII code of the character to be drawn.
 * @param color The color to use for drawing the character.
 */
void drawChar(int x, int y, char asciiCode, uint32_t color)
{
    const uint8_t *charBitmap = &font_data[asciiCode << 3]; ///< Pointer to the character's bitmap data.

    for (int Y = 0; Y < 8; ++Y)
    {
        uint8_t bitRow = charBitmap[Y]; ///< Row of the bitmap to be drawn.
        for (int X = 0; X < 8; ++X)
        {
#define onDrawPixel ((bitRow >> X) & 0b00000001) ///< Check if the pixel should be drawn.

            if (onDrawPixel)
                pixel(x + X, y + Y, color); ///< Draw the pixel if it is set in the bitmap.
        }
    }
}

/**
 * @brief Draw a string of text at a specified position.
 *
 * This function renders a string of text using the `drawChar` function. Each character in the string
 * is drawn sequentially with the specified color. The text wraps to the next line if a newline character
 * ('\n') is encountered.
 *
 * @param x The x-coordinate of the position where the text should start.
 * @param y The y-coordinate of the position where the text should start.
 * @param text The null-terminated string to be drawn.
 * @param color The color to use for drawing the text.
 */
void drawText(int x, int y, char *text, uint32_t color)
{
    char *c = text;     ///< Pointer to the current character in the text.
    register int X = x; ///< Current x-coordinate for drawing.
    register int Y = y; ///< Current y-coordinate for drawing.

    while (*c)
    {
        if (*c == '\n')
        {
            X = x;   ///< Reset x-coordinate to the start of the line.
            Y += 12; ///< Move y-coordinate down for the next line.
            ++c;     ///< Move to the next character.
            continue;
        }

        drawChar(X, Y, *c, color); ///< Draw the current character.

        X += 8; ///< Move x-coordinate to the right for the next character.
        ++c;    ///< Move to the next character.
    }
}

/**
 * @brief Draw formatted text at a specified position.
 *
 * This function allows for formatted text to be drawn at a specified position using a format string
 * similar to `printf`. The formatted text is rendered using the `drawText` function.
 *
 * @param x The x-coordinate of the position where the formatted text should start.
 * @param y The y-coordinate of the position where the formatted text should start.
 * @param color The color to use for drawing the formatted text.
 * @param format The format string (similar to printf) that specifies how to format the text.
 * @param ... The values to be formatted and included in the text.
 */
void drawFormattedText(int x, int y, uint32_t color, const char *format, ...)
{
    char buffer[1024] = {0};        ///< Buffer to hold the formatted text.
    va_list args;                   ///< Variable argument list for the formatted text.
    va_start(args, format);         ///< Initialize the variable argument list.
    vsprintf(buffer, format, args); ///< Format the text and store it in the buffer.
    va_end(args);                   ///< Clean up the variable argument list.
    drawText(x, y, buffer, color);  ///< Draw the formatted text using `drawText`.
}

#endif