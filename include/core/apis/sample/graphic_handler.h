#ifndef GRAPHIC_API_HANDLER_SAMPLE_IMPLEMENTATION_H
#define GRAPHIC_API_HANDLER_SAMPLE_IMPLEMENTATION_H

#include <stdbool.h> // For boolean type and constants
#include <stdint.h>  // For fixed-width integer types

/**
 * Sets the window title for the SDL window.
 *
 * @param title The title to be displayed in the window’s title bar.
 */
void setWindowTitle(const char *title) {}

/**
 * Initializes SDL and the graphics engine with the specified screen dimensions and window title.
 *
 * @param screenWidth Width of the screen in pixels.
 * @param screenHeight Height of the screen in pixels.
 * @param windowTitle The title of the SDL window.
 */
bool initializeGraphicApi(int widthScreenPixels, int heightScreenPixels, const char *windowTitle) { return true; }

/**
 * Cleans up and shuts down the graphics engine.
 */
void closeGraphicApi() {}

#endif