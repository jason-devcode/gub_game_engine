#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "../fast_math.h"

#include "camera/camera_properties.h"

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

#endif