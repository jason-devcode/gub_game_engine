#ifndef VECTORIAL_2D_CALCULUS_H
#define VECTORIAL_2D_CALCULUS_H

#include <math.h>
#include "fast_math.h" // For fast inv_sqrt and fast sqrt

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
 * @brief Multiplies a 2D vector by a scalar.
 *
 * @param v Vector to be multiplied.
 * @param scalar Scalar value to multiply the vector by.
 * @return Resultant vector after multiplication.
 */
INLINE Vec2f vec2f_multiply_scalar(Vec2f v, double scalar)
{
    return (Vec2f){v.x * scalar, v.y * scalar};
}

/**
 * @brief Multiplies two 2D vectors component-wise.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant vector after component-wise multiplication.
 */
INLINE Vec2f vec2f_multiply_vector(Vec2f v1, Vec2f v2)
{
    return (Vec2f){v1.x * v2.x, v1.y * v2.y};
}

/**
 * @brief Divides a 2D vector by a scalar with protection against division by zero.
 *
 * @param v Vector to be divided.
 * @param scalar Scalar value to divide the vector by.
 * @return Resultant vector after division. Returns the original vector if the scalar is zero.
 */
INLINE Vec2f vec2f_divide_scalar(Vec2f v, double scalar)
{
    if (scalar == 0.0)
    {
        // Handle division by zero (return the original vector or handle it differently if needed)
        return v;
    }
    return (Vec2f){v.x / scalar, v.y / scalar};
}

/**
 * @brief Divides two 2D vectors component-wise with protection against division by zero.
 *
 * @param v1 First vector (numerator).
 * @param v2 Second vector (denominator).
 * @return Resultant vector after component-wise division. Returns the original vector for any component if the corresponding denominator component is zero.
 */
INLINE Vec2f vec2f_divide_vector(Vec2f v1, Vec2f v2)
{
    return (Vec2f){
        v2.x != 0.0 ? v1.x / v2.x : v1.x,
        v2.y != 0.0 ? v1.y / v2.y : v1.y};
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

/**
 * @brief Rotates a 2D vector by a specified angle and returns a new vector.
 *
 * This function calculates the rotated position of a vector based on
 * the provided angle (in radians) and returns a new `Vec2f` vector with
 * the rotated coordinates.
 *
 * @param v The original 2D vector to be rotated.
 * @param angleInRadians The angle by which to rotate the vector, in radians.
 * @return A new `Vec2f` vector representing the rotated vector.
 */
INLINE Vec2f vec2f_rotate_by_angle(Vec2f v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    return (Vec2f){
        v.x * cosine_value - v.y * sine_value,
        v.y * cosine_value + v.x * sine_value};
}

/**
 * @brief Rotates a 2D vector in place by a specified angle.
 *
 * This function rotates the original vector (pointed to by the input pointer)
 * based on the provided angle (in radians) and updates the vector's coordinates
 * in place.
 *
 * @param v Pointer to the `Vec2f` vector to be rotated in place.
 * @param angleInRadians The angle by which to rotate the vector, in radians.
 */
INLINE void vec2f_rotate_in_place(Vec2f *v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    const double tempX = v->x;
    const double tempY = v->y;

    v->x = tempX * cosine_value - tempY * sine_value;
    v->y = tempY * cosine_value + tempX * sine_value;
}

#endif // VECTORIAL_2D_CALCULUS_H