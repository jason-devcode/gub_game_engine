#ifndef FAST_MATH_H
#define FAST_MATH_H

// Inline keyword for potentially faster function calls
#define INLINE static inline

/**
 * @brief Computes the fast inverse square root of a number.
 *
 * This function uses the famous Quake III Arena method to compute 1/sqrt(x) quickly.
 *
 * @param number The number for which the inverse square root is to be computed.
 * @return The fast inverse square root of the input number.
 */
INLINE float fast_inv_sqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(long *)&y;           // Evil bit-level hacking
    i = 0x5f3759df - (i >> 1); // What the magic number does
    y = *(float *)&i;          // Back to float

    // One iteration of Newton's method to improve the approximation
    y *= (threehalfs - (x2 * y * y));
    y *= (threehalfs - (x2 * y * y)); // Optional: Repeat for higher precision

    return y;
}

/**
 * @brief Computes the fast square root of a number.
 *
 * This macro uses the fast inverse square root function to compute the square root quickly.
 *
 * @param number The number for which the square root is to be computed.
 * @return The fast square root of the input number.
 */
#define fast_sqrt(number) (1.0f / fast_inv_sqrt(number))

#endif // FAST_MATH_H