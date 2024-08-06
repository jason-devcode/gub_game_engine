#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "../fast_math.h"

#include "camera/camera_properties.h"

/**
 * @brief Moves the camera forward in the direction it is currently facing.
 */
static void moveCameraForward()
{
    cameraPosition.x += cameraDirection.x * deltatime * 0.001;
    cameraPosition.y += cameraDirection.y * deltatime * 0.001;
    cameraPosition.z += cameraDirection.z * deltatime * 0.001;
}

/**
 * @brief Moves the camera backward opposite to the direction it is currently facing.
 */
static void moveCameraBackward()
{
    cameraPosition.x -= cameraDirection.x * deltatime * 0.001;
    cameraPosition.y -= cameraDirection.y * deltatime * 0.001;
    cameraPosition.z -= cameraDirection.z * deltatime * 0.001;
}

/**
 * @brief Moves the camera to the left relative to its current position.
 */
static void moveCameraLeft()
{
    cameraPosition.x -= getDeltatime() * 0.01;
}

/**
 * @brief Moves the camera to the right relative to its current position.
 */
static void moveCameraRight()
{
    cameraPosition.x += getDeltatime() * 0.01;
}

/**
 * @brief Moves the camera upwards relative to its current position.
 */
static void moveCameraUp()
{
    cameraPosition.y += getDeltatime() * 0.01;
}

/**
 * @brief Moves the camera downwards relative to its current position.
 */
static void moveCameraDown()
{
    cameraPosition.y -= getDeltatime() * 0.01;
}

/**
 * @brief Updates the direction vector of the camera based on its pitch, yaw, and roll angles.
 */
static void updateCameraDirection()
{
    cosineCameraPitch = fast_cosine(cameraPitch), sineCameraPitch = fast_sine(cameraPitch);
    cosineCameraYaw = fast_cosine(cameraYaw), sineCameraYaw = fast_sine(cameraYaw);
    cosineCameraRoll = fast_cosine(cameraRoll), sineCameraRoll = fast_sine(cameraRoll);

    double tempX = 0.0, X = 0;
    double tempY = 0.0, Y = 0;
    double tempZ = 1.0, Z = 0;

    // rotate X Axis - ZY plane pitch
    Z = tempZ * cosineCameraPitch - tempY * sineCameraPitch;
    Y = tempY * cosineCameraPitch + tempZ * sineCameraPitch;
    tempZ = Z;
    tempY = Y;

    // rotate Y Axis - XZ plane yaw
    X = tempX * cosineCameraYaw + tempZ * sineCameraYaw;
    Z = tempZ * cosineCameraYaw - tempX * sineCameraYaw;
    tempX = X;
    tempZ = Z;

    // rotate Z Axis - XY plane roll
    X = tempX * cosineCameraRoll - tempY * sineCameraRoll;
    Y = tempY * cosineCameraRoll + tempX * sineCameraRoll;
    tempX = X;
    tempY = Y;

    cameraDirection.x = tempX;
    cameraDirection.y = tempY;
    cameraDirection.z = tempZ;
}

/**
 * @brief Rotates the camera around the yaw axis.
 *
 * @param angle The angle to rotate the camera by, in radians.
 */
static void rotateCameraYaw(double angle)
{
    cameraYaw += angle * getDeltatime() * 0.01;
    updateCameraDirection();
}

/**
 * @brief Rotates the camera around the pitch axis.
 *
 * @param angle The angle to rotate the camera by, in radians.
 */
static void rotateCameraPitch(double angle)
{
    cameraPitch += angle * getDeltatime() * 0.01;
    updateCameraDirection();
}

/**
 * @brief Rotates the camera around the roll axis.
 *
 * @param angle The angle to rotate the camera by, in radians.
 */
static void rotateCameraRoll(double angle)
{
    cameraRoll += angle * getDeltatime() * 0.01;
    updateCameraDirection();
}

/**
 * @brief Initializes the 3D camera with the given position, angles, and horizontal field of view.
 *
 * @param initialPosition The initial position of the camera.
 * @param initialAngle The initial pitch, yaw, and roll angles of the camera.
 * @param horizontalFov The horizontal field of view of the camera.
 */
static void initializeCamera3D(Vec3f initialPosition, Vec3f initialAngle, double horizontalFov)
{
    cameraFrustumHorizontalFov = horizontalFov;

    cameraPosition.x = initialPosition.x;
    cameraPosition.y = initialPosition.y;
    cameraPosition.z = initialPosition.z;

    cameraPitch = initialAngle.x;
    cameraYaw = initialAngle.y;
    cameraRoll = initialAngle.z;

    updateCameraDirection();
}

#endif