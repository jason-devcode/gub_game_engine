#ifndef FAST_TANGENT_FUNCTION_H
#define FAST_TANGENT_FUNCTION_H

#include "../trigonometry.h" // For trigonometry utilities
#include "fast_abs.h"        // For fast abs

/**
 * @brief Precomputed table of tangent values for angles from 0 to 359 degrees.
 *
 * Provides fast lookup of tangent values for angles from 0 to 359 degrees.
 * Generated and stored in "tangent_table.data".
 */
static const double tangent_table[360] = {
#include "../math_data/tangent_table.data"
};

/**
 * @brief Computes the tangent of an angle in radians using a precomputed table.
 *
 * Approximates the tangent value by converting radians to degrees, normalizing to [0, 359],
 * and looking up the value in the precomputed table.
 *
 * @param angleInRadians The angle in radians for which the tangent value is to be computed.
 * @return The approximated tangent value of the given angle.
 */
static inline double fast_tangent(double angleInRadians)
{
    int angleInDegrees = ((int)radiansToDegrees(angleInRadians) % 360);
    angleInDegrees = fast_abs(angleInDegrees);
    return tangent_table[angleInDegrees];
}

#endif // FAST_TANGENT_FUNCTION_H