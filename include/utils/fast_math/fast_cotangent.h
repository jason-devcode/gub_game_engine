#ifndef FAST_COTANGENT_FUNCTION_H
#define FAST_COTANGENT_FUNCTION_H

#include "../math_constants.h" // For trigonometry utilities
#include "fast_abs.h"        // For fast abs

/**
 * @brief Precomputed table of cotangent values for angles from 0 to 359 degrees.
 *
 * Provides fast lookup of cotangent values for angles from 0 to 359 degrees.
 * Generated and stored in "cotangent_table.data".
 */
static const double cotangent_table[360] = {
#include "../math_data/cotangent_table.data"
};

/**
 * @brief Computes the cotangent of an angle in radians using a precomputed table.
 *
 * Approximates the cotangent value by converting radians to degrees, normalizing to [0, 359],
 * and looking up the value in the precomputed table.
 *
 * @param angleInRadians The angle in radians for which the cotangent value is to be computed.
 * @return The approximated cotangent value of the given angle.
 */
static inline double fast_cotangent(double angleInRadians)
{
    int angleInDegrees = ((int)radiansToDegrees(angleInRadians) % 360);
    angleInDegrees = (angleInDegrees < 0) ? 360 + angleInDegrees : angleInDegrees;
    return cotangent_table[angleInDegrees];
}

#endif // FAST_COTANGENT_FUNCTION_H