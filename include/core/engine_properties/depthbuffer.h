#ifndef DEPTH_BUFFER_H
#define DEPTH_BUFFER_H

#include <stdlib.h>

/**
 * @brief Pointer to the depth buffer.
 *
 * The depth buffer is used to store depth information (z-coordinates) for each pixel on the screen.
 * It is typically used in 3D rendering to determine which objects are in front of others.
 */
double *depthbuffer = NULL;

#endif