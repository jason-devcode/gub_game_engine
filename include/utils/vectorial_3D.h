#ifndef VECTORIAL_3D_CALCULUS_H
#define VECTORIAL_3D_CALCULUS_H

#include <math.h>
#include "fast_math.h" // For fast math operations

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

/**
 * @brief Rotates a 3D vector around the X axis by a specified angle.
 *
 * This function calculates the rotated position of a vector around the X axis
 * based on the provided angle (in radians) and returns a new `Vec3f` vector
 * with the rotated coordinates.
 *
 * @param v The original 3D vector to be rotated.
 * @param angleInRadians The angle by which to rotate the vector around the X axis, in radians.
 * @return A new `Vec3f` vector representing the rotated vector.
 */
INLINE Vec3f vec3f_rotate_x(Vec3f v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    return (Vec3f){
        v.x,
        v.y * cosine_value - v.z * sine_value,
        v.y * sine_value + v.z * cosine_value};
}

/**
 * @brief Rotates a 3D vector in place around the X axis by a specified angle.
 *
 * This function rotates the original vector (pointed to by the input pointer)
 * around the X axis based on the provided angle (in radians) and updates the
 * vector's coordinates in place.
 *
 * @param v Pointer to the `Vec3f` vector to be rotated in place.
 * @param angleInRadians The angle by which to rotate the vector around the X axis, in radians.
 */
INLINE void vec3f_rotate_x_in_place(Vec3f *v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    const double tempY = v->y;
    const double tempZ = v->z;

    v->y = tempY * cosine_value - tempZ * sine_value;
    v->z = tempY * sine_value + tempZ * cosine_value;
}

/**
 * @brief Rotates a 3D vector around the Y axis by a specified angle.
 *
 * This function calculates the rotated position of a vector around the Y axis
 * based on the provided angle (in radians) and returns a new `Vec3f` vector
 * with the rotated coordinates.
 *
 * @param v The original 3D vector to be rotated.
 * @param angleInRadians The angle by which to rotate the vector around the Y axis, in radians.
 * @return A new `Vec3f` vector representing the rotated vector.
 */
INLINE Vec3f vec3f_rotate_y(Vec3f v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    return (Vec3f){
        v.x * cosine_value + v.z * sine_value,
        v.y,
        -v.x * sine_value + v.z * cosine_value};
}

/**
 * @brief Rotates a 3D vector in place around the Y axis by a specified angle.
 *
 * This function rotates the original vector (pointed to by the input pointer)
 * around the Y axis based on the provided angle (in radians) and updates the
 * vector's coordinates in place.
 *
 * @param v Pointer to the `Vec3f` vector to be rotated in place.
 * @param angleInRadians The angle by which to rotate the vector around the Y axis, in radians.
 */
INLINE void vec3f_rotate_y_in_place(Vec3f *v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    const double tempX = v->x;
    const double tempZ = v->z;

    v->x = tempX * cosine_value + tempZ * sine_value;
    v->z = -tempX * sine_value + tempZ * cosine_value;
}

/**
 * @brief Rotates a 3D vector around the Z axis by a specified angle.
 *
 * This function calculates the rotated position of a vector around the Z axis
 * based on the provided angle (in radians) and returns a new `Vec3f` vector
 * with the rotated coordinates.
 *
 * @param v The original 3D vector to be rotated.
 * @param angleInRadians The angle by which to rotate the vector around the Z axis, in radians.
 * @return A new `Vec3f` vector representing the rotated vector.
 */
INLINE Vec3f vec3f_rotate_z(Vec3f v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    return (Vec3f){
        v.x * cosine_value - v.y * sine_value,
        v.x * sine_value + v.y * cosine_value,
        v.z};
}

/**
 * @brief Rotates a 3D vector in place around the Z axis by a specified angle.
 *
 * This function rotates the original vector (pointed to by the input pointer)
 * around the Z axis based on the provided angle (in radians) and updates the
 * vector's coordinates in place.
 *
 * @param v Pointer to the `Vec3f` vector to be rotated in place.
 * @param angleInRadians The angle by which to rotate the vector around the Z axis, in radians.
 */
INLINE void vec3f_rotate_z_in_place(Vec3f *v, float angleInRadians)
{
    const double sine_value = fast_sine(angleInRadians);
    const double cosine_value = fast_cosine(angleInRadians);

    const double tempX = v->x;
    const double tempY = v->y;

    v->x = tempX * cosine_value - tempY * sine_value;
    v->y = tempX * sine_value + tempY * cosine_value;
}

/**
 * @brief Rotates a 3D vector around the X, Y, and Z axes sequentially by specified angles.
 *
 * This function calculates the rotated position of a vector based on the provided
 * angles (in radians) for rotations around the X, Y, and Z axes, respectively.
 * The rotations are applied in the order: X -> Y -> Z.
 *
 * @param v The original 3D vector to be rotated.
 * @param angleX The angle by which to rotate the vector around the X axis, in radians.
 * @param angleY The angle by which to rotate the vector around the Y axis, in radians.
 * @param angleZ The angle by which to rotate the vector around the Z axis, in radians.
 * @return A new `Vec3f` vector representing the rotated vector.
 */
INLINE Vec3f vec3f_rotate_xyz(Vec3f v, float angleX, float angleY, float angleZ)
{
    // Rotation around X axis
    const double sineX = fast_sine(angleX);
    const double cosineX = fast_cosine(angleX);
    Vec3f temp;
    temp.x = v.x;
    temp.y = v.y * cosineX - v.z * sineX;
    temp.z = v.y * sineX + v.z * cosineX;

    // Rotation around Y axis
    const double sineY = fast_sine(angleY);
    const double cosineY = fast_cosine(angleY);
    v.x = temp.x * cosineY + temp.z * sineY;
    v.y = temp.y;
    v.z = -temp.x * sineY + temp.z * cosineY;

    // Rotation around Z axis
    const double sineZ = fast_sine(angleZ);
    const double cosineZ = fast_cosine(angleZ);
    return (Vec3f){
        v.x * cosineZ - v.y * sineZ,
        v.x * sineZ + v.y * cosineZ,
        v.z};
}

/**
 * @brief Rotates a 3D vector in place around the X, Y, and Z axes sequentially by specified angles.
 *
 * This function rotates the original vector (pointed to by the input pointer) based on the provided
 * angles (in radians) for rotations around the X, Y, and Z axes, respectively. The rotations
 * are applied in the order: X -> Y -> Z, and the vector is updated in place.
 *
 * @param v Pointer to the `Vec3f` vector to be rotated in place.
 * @param angleX The angle by which to rotate the vector around the X axis, in radians.
 * @param angleY The angle by which to rotate the vector around the Y axis, in radians.
 * @param angleZ The angle by which to rotate the vector around the Z axis, in radians.
 */
INLINE void vec3f_rotate_xyz_in_place(Vec3f *v, float angleX, float angleY, float angleZ)
{
    // Rotation around X axis
    const double sineX = fast_sine(angleX);
    const double cosineX = fast_cosine(angleX);
    double tempY = v->y;
    double tempZ = v->z;

    v->y = tempY * cosineX - tempZ * sineX;
    v->z = tempY * sineX + tempZ * cosineX;

    // Rotation around Y axis
    const double sineY = fast_sine(angleY);
    const double cosineY = fast_cosine(angleY);
    double tempX = v->x;

    v->x = tempX * cosineY + v->z * sineY;
    v->z = -tempX * sineY + v->z * cosineY;

    // Rotation around Z axis
    const double sineZ = fast_sine(angleZ);
    const double cosineZ = fast_cosine(angleZ);

    tempX = v->x;
    tempY = v->y;

    v->x = tempX * cosineZ - tempY * sineZ;
    v->y = tempX * sineZ + tempY * cosineZ;
}

#endif // VECTORIAL_3D_CALCULUS_H