#ifndef FAST_INVERSE_SQRT_H
#define FAST_INVERSE_SQRT_H

/**
 * @file fast_inverse_sqrt.h
 * @brief Provides a fast method to compute the inverse square root of a number.
 *
 * Implements the Quake III Arena algorithm for rapid calculation of 1/sqrt(x).
 */

/**
 * @brief Computes the fast inverse square root of a number.
 *
 * Uses the Quake III Arena method for a quick approximation of 1/sqrt(x), including
 * one iteration of Newton's method for improved accuracy.
 *
 * @param number The number for which the inverse square root is computed.
 * @return The approximate inverse square root of the input number.
 */
static inline float fast_inv_sqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(long *)&y;           // Bit-level manipulation
    i = 0x5f3759df - (i >> 1); // Magic number
    y = *(float *)&i;          // Convert back to float

    // Improve approximation with one iteration of Newton's method
    y *= (threehalfs - (x2 * y * y));
    y *= (threehalfs - (x2 * y * y)); // Optional: Higher precision

    return y;
}

#endif // FAST_INVERSE_SQRT_H