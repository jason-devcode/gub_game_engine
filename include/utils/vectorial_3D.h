#ifndef VECTORIAL_3D_CALCULUS_H
#define VECTORIAL_3D_CALCULUS_H

#include <math.h>
#include <fast_math.h> // Assuming this is a custom or third-party library for fast mathematical operations

// Inline keyword for potentially faster function calls
#define INLINE static inline

// Struct for 3D vector with floating-point components
typedef struct
{
    double x, y, z;
} Vec3f;

/**
 * @brief Adds two 3D vectors.
 * 
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant vector after addition.
 */
INLINE Vec3f vec3f_add(Vec3f v1, Vec3f v2)
{
    return (Vec3f){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

/**
 * @brief Subtracts the second 3D vector from the first.
 * 
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant vector after subtraction.
 */
INLINE Vec3f vec3f_subtract(Vec3f v1, Vec3f v2)
{
    return (Vec3f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

/**
 * @brief Calculates the dot product of two 3D vectors.
 * 
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product of the vectors.
 */
INLINE double vec3f_dot(Vec3f v1, Vec3f v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/**
 * @brief Calculates the cross product of two 3D vectors.
 * 
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant vector after cross product.
 */
INLINE Vec3f vec3f_cross(Vec3f v1, Vec3f v2)
{
    return (Vec3f){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x};
}

/**
 * @brief Calculates the inverse of the magnitude (1 / magnitude) of a 3D vector.
 * 
 * @param v Vector for which the inverse of the magnitude is to be calculated.
 * @return Inverse of the magnitude of the vector.
 */
INLINE double vec3f_inv_magnitude(Vec3f v)
{
    return fast_inv_sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/**
 * @brief Calculates the magnitude of a 3D vector.
 * 
 * @param v Vector for which the magnitude is to be calculated.
 * @return Magnitude of the vector.
 */
INLINE double vec3f_magnitude(Vec3f v)
{
    return fast_sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/**
 * @brief Normalizes a 3D vector (scales it to have a magnitude of 1).
 * 
 * @param v Vector to be normalized.
 * @return Normalized vector.
 */
INLINE Vec3f vec3f_normalize(Vec3f v)
{
    double inv_mag = vec3f_inv_magnitude(v);
    return (Vec3f){v.x * inv_mag, v.y * inv_mag, v.z * inv_mag};
}

#endif // VECTORIAL_3D_CALCULUS_H