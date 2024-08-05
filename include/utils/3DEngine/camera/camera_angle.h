#ifndef CAMERA_3D_ANGLE
#define CAMERA_3D_ANGLE

static double cameraPitch = 0.0; // X Axis camera angle rotation
static double cameraYaw = 0.0;   // Y Axis camera angle rotation
static double cameraRoll = 0.0;  // Z Axis camera angle rotation

// pre-cached cosine and sine values for view rotation
static double cosineCameraPitch = 0.0, sineCameraPitch = 0.0;
static double cosineCameraYaw = 0.0, sineCameraYaw = 0.0;
static double cosineCameraRoll = 0.0, sineCameraRoll = 0.0;

#endif