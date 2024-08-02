#ifndef FAST_SINE_FUNCTION_H
#define FAST_SINE_FUNCTION_H

#include "../trigonometry.h" // For trigonometry utilities
#include "fast_abs.h"        // For fast abs

/**
 * @brief Precomputed table of sine values for angles from 0 to 359 degrees.
 *
 * Provides fast lookup of sine values for angles from 0 to 359 degrees.
 * Generated and stored in "sine_table.data".
 */
static const double sine_table[360] = {
#include "../math_data/sine_table.data"
};

/**
 * @brief Computes the sine of an angle in radians using a precomputed table.
 *
 * Approximates the sine value by converting radians to degrees, normalizing to [0, 359],
 * and looking up the value in the precomputed table.
 *
 * @param angleInRadians The angle in radians for which the sine value is to be computed.
 * @return The approximated sine value of the given angle.
 */
static inline double fast_sine(double angleInRadians)
{
    int angleInDegrees = ((int)radiansToDegrees(angleInRadians) % 360);
    angleInDegrees = fast_abs(angleInDegrees);
    return sine_table[angleInDegrees];
}

#endif // FAST_SINE_FUNCTION_H