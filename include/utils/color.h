/**
 * @file color_utils.h
 * @brief Macros and functions for handling color operations.
 */

#ifndef COLOR_UTILS
#define COLOR_UTILS

#include "byte.h"

/**
 * @brief Extract the alpha channel from a color.
 * @param color The color value.
 * @return The alpha channel value.
 */
#define GETA(color) (EXTRACT_BYTE(color, 3))

/**
 * @brief Extract the red channel from a color.
 * @param color The color value.
 * @return The red channel value.
 */
#define GETR(color) (EXTRACT_BYTE(color, 2))

/**
 * @brief Extract the green channel from a color.
 * @param color The color value.
 * @return The green channel value.
 */
#define GETG(color) (EXTRACT_BYTE(color, 1))

/**
 * @brief Extract the blue channel from a color.
 * @param color The color value.
 * @return The blue channel value.
 */
#define GETB(color) (EXTRACT_BYTE(color, 0))

/**
 * @brief Create an RGB color value from individual channels.
 * @param r The red channel value.
 * @param g The green channel value.
 * @param b The blue channel value.
 * @return The RGB color value.
 */
#define RGB(r, g, b) (uint32_t)(INSERT_BYTE(0xFF, 3) | INSERT_BYTE((r), 2) | INSERT_BYTE((g), 1) | INSERT_BYTE((b), 0))

/**
 * @brief Create an RGBA color value from individual channels.
 * @param r The red channel value.
 * @param g The green channel value.
 * @param b The blue channel value.
 * @param a The alpha channel value.
 * @return The RGBA color value.
 */
#define RGBA(r, g, b, a) (INSERT_BYTE(a, 3) | INSERT_BYTE(r, 2) | INSERT_BYTE(g, 1) | INSERT_BYTE(b, 0))

/**
 * @brief Clamp a color channel value to the range [0, 255].
 * @param x The value to clamp.
 * @return The clamped value.
 */
#define clampColorChannel(x) ((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))

/**
 * @brief Adjust the brightness of an RGB color.
 *
 * Adjust the brightness of the given color by the specified factor.
 * A factor greater than 1.0 increases brightness, while a factor less than 1.0 decreases brightness.
 *
 * @param color The original RGB color.
 * @param factor The brightness adjustment factor.
 * @return The brightness-adjusted RGB color.
 */
static inline uint32_t adjustColorBrightness(uint32_t color, double factor)
{
    uint8_t R = clampColorChannel((int)(GETR(color) * factor));
    uint8_t G = clampColorChannel((int)(GETG(color) * factor));
    uint8_t B = clampColorChannel((int)(GETB(color) * factor));

    return RGB(R, G, B);
}

/**
 * @brief Linearly interpolates three colors based on given weights.
 *
 * Calculates a new color by linearly interpolating the input colors `color1`, `color2`, and `color3`
 * using the corresponding weights `alpha`, `beta`, and `gamma`. The weights should sum to 1.0.
 *
 * @param color1 The first color to interpolate.
 * @param color2 The second color to interpolate.
 * @param color3 The third color to interpolate.
 * @param alpha The weight for the first color.
 * @param beta The weight for the second color.
 * @param gamma The weight for the third color.
 *
 * @return A new color representing the interpolated result.
 */
#define triangularColorMix(color1, color2, color3, alpha, beta, gamma)                                          \
    RGB(                                                                                                        \
        ((uint8_t)((double)GETR(color1) * alpha + (double)GETR(color2) * beta + (double)GETR(color3) * gamma)), \
        ((uint8_t)((double)GETG(color1) * alpha + (double)GETG(color2) * beta + (double)GETG(color3) * gamma)), \
        ((uint8_t)((double)GETB(color1) * alpha + (double)GETB(color2) * beta + (double)GETB(color3) * gamma)))

#endif // COLOR_UTILS