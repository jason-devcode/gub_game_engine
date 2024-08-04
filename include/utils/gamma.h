/**
 * @file gamma_correction_utils.h
 * @brief Utilities for gamma correction on RGB colors.
 *
 * This header file provides functions and macros for applying gamma correction
 * to RGB colors. It includes both a slow, precise method using mathematical
 * calculations and a fast method using a precomputed gamma correction table.
 */

#ifndef GAMMA_CORRECTION_UTILS_H
#define GAMMA_CORRECTION_UTILS_H

#include "color.h"
#include <math.h>

#define GAMMA_TABLE_SIZE 256

/**
 * @brief Precomputed gamma correction table.
 *
 * This table is used for fast gamma correction. It contains precomputed values
 * for gamma correction with a gamma factor of 2.2.
 */
uint8_t gammaTable[GAMMA_TABLE_SIZE] = {
#include "gamma_data/gamma_2.2.data"
};

/**
 * @brief Apply gamma correction to an RGB color using a specified gamma factor.
 *
 * This function applies gamma correction to the given color using the specified
 * gamma factor. It performs the correction for each color channel (red, green,
 * and blue) and returns the corrected color.
 *
 * @param color The original RGB color.
 * @param gammaFactor The gamma factor to apply.
 * @return The gamma-corrected RGB color.
 */
static inline uint32_t applyGammaCorrection(uint32_t color, double gammaFactor)
{
    double R = (double)GETR(color) / 255.0; // Decimal representation of the red channel [0-1]
    double G = (double)GETG(color) / 255.0; // Decimal representation of the green channel [0-1]
    double B = (double)GETB(color) / 255.0; // Decimal representation of the blue channel [0-1]

    uint8_t newR = (uint8_t)(pow(R, 1 / gammaFactor) * 255.0);
    uint8_t newG = (uint8_t)(pow(G, 1 / gammaFactor) * 255.0);
    uint8_t newB = (uint8_t)(pow(B, 1 / gammaFactor) * 255.0);

    return RGB(newR, newG, newB);
}
/**
 * @brief Apply inverse gamma correction to an RGB color.
 *
 * This function reverts gamma correction on the given color using the specified
 * gamma factor. It performs the correction for each color channel (red, green,
 * and blue) and returns the corrected color.
 *
 * @param color The gamma-corrected RGB color.
 * @param gammaFactor The gamma factor to revert.
 * @return The original RGB color before gamma correction.
 */
static inline uint32_t applyInverseGammaCorrection(uint32_t color, double gammaFactor)
{
    double R = (double)GETR(color) / 255.0;
    double G = (double)GETG(color) / 255.0;
    double B = (double)GETB(color) / 255.0;

    uint8_t newR = (uint8_t)(pow(R, gammaFactor) * 255.0);
    uint8_t newG = (uint8_t)(pow(G, gammaFactor) * 255.0);
    uint8_t newB = (uint8_t)(pow(B, gammaFactor) * 255.0);

    return RGB(newR, newG, newB);
}

/**
 * @brief Generate a gamma correction table for a specified gamma factor.
 *
 * This function generates a gamma correction table for the given gamma factor.
 * The table can then be used for fast gamma correction.
 *
 * @param gammaTable The array to store the gamma correction values.
 * @param gammaFactor The gamma factor to use for generating the table.
 */
static inline void generateGammaTable(uint8_t gammaTable[GAMMA_TABLE_SIZE], double gammaFactor)
{
    for (int i = 0; i < GAMMA_TABLE_SIZE; ++i)
    {
        gammaTable[i] = (uint8_t)(pow((double)i / 255.0, 1.0 / gammaFactor) * 255.0);
    }
}

/**
 * @brief Apply fast gamma correction to an RGB color.
 *
 * This macro applies gamma correction to the given color using a precomputed
 * gamma correction table. It is significantly faster than the precise method
 * but only works for the gamma factor used to generate the table.
 *
 * @param color The original RGB color.
 * @return The gamma-corrected RGB color.
 */
#define fast_apply_gamma_correction(color) \
    RGB(gammaTable[GETR(color)], gammaTable[GETG(color)], gammaTable[GETB(color)])

#endif // GAMMA_CORRECTION_UTILS_H