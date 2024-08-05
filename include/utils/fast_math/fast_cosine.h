#ifndef FAST_COSINE_FUNCTION_H
#define FAST_COSINE_FUNCTION_H

#include "../math_constants.h" // For trigonometry utilities
#include "fast_abs.h"          // For fast abs

/**
 * @brief Precomputed table of cosine values for angles from 0 to 359 degrees.
 *
 * Provides fast lookup of cosine values for angles from 0 to 359 degrees.
 * Generated and stored in "cosine_table.data".
 */
static const double cosine_table[360] = {
#include "../math_data/cosine_table.data"
};

/**
 * @brief Computes the cosine of an angle in radians using a precomputed table.
 *
 * Approximates the cosine value by converting radians to degrees, normalizing to [0, 359],
 * and looking up the value in the precomputed table.
 *
 * @param angleInRadians The angle in radians for which the cosine value is to be computed.
 * @return The approximated cosine value of the given angle.
 */
static inline double fast_cosine(double angleInRadians)
{
    int angleInDegrees = ((int)radiansToDegrees(angleInRadians) % 360);
    angleInDegrees = (angleInDegrees < 0) ? 360 + angleInDegrees : angleInDegrees;
    return cosine_table[angleInDegrees];
}

#endif // FAST_COSINE_FUNCTION_H