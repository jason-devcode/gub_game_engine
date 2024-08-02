#ifndef VECTORIAL_2D_CALCULUS_H
#define VECTORIAL_2D_CALCULUS_H

#include <math.h>
#include <fast_math.h> // For fast inv_sqrt and fast sqrt

// Inline keyword for potentially faster function calls
#define INLINE static inline

// Struct for 2D vector with floating-point components
typedef struct
{
    double x, y;
} Vec2f;

/**
 * @brief Adds two 2D vectors.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant vector after addition.
 */
INLINE Vec2f vec2f_add(Vec2f v1, Vec2f v2)
{
    return (Vec2f){v1.x + v2.x, v1.y + v2.y};
}

/**
 * @brief Subtracts the second 2D vector from the first.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant vector after subtraction.
 */
INLINE Vec2f vec2f_subtract(Vec2f v1, Vec2f v2)
{
    return (Vec2f){v1.x - v2.x, v1.y - v2.y};
}

/**
 * @brief Calculates the dot product of two 2D vectors.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product of the vectors.
 */
INLINE double vec2f_dot(Vec2f v1, Vec2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/**
 * @brief Calculates the inverse of the magnitude (1 / magnitude) of a 2D vector.
 *
 * @param v Vector for which the inverse of the magnitude is to be calculated.
 * @return Inverse of the magnitude of the vector.
 */
INLINE double vec2f_inv_magnitude(Vec2f v) // 1 / magnitude
{
    return fast_inv_sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief Calculates the magnitude of a 2D vector.
 *
 * @param v Vector for which the magnitude is to be calculated.
 * @return Magnitude of the vector.
 */
INLINE double vec2f_magnitude(Vec2f v)
{
    return fast_sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief Normalizes a 2D vector (scales it to have a magnitude of 1).
 *
 * @param v Vector to be normalized.
 * @return Normalized vector.
 */
INLINE Vec2f vec2f_normalize(Vec2f v)
{
    double inv_mag = vec2f_inv_magnitude(v);
    return (Vec2f){v.x * inv_mag, v.y * inv_mag};
}

#endif // VECTORIAL_2D_CALCULUS_H