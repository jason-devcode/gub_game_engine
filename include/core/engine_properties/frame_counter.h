#ifndef FRAME_COUNTER_H
#define FRAME_COUNTER_H

#include <stdint.h>

/**
 * @brief Holds the count of frames rendered.
 *
 * This variable keeps track of the number of frames that have been rendered
 * since the last reset or initialization. It is incremented as frames are processed.
 */
static uint32_t frameCounter = 0;

/**
 * @brief Increments the frame counter.
 *
 * This macro increases the `frameCounter` by one, typically called once per frame
 * to keep track of the total number of frames rendered.
 */
#define updateFrameCounter() ++frameCounter

/**
 * @brief Sets the frame counter to a specific value.
 *
 * This macro sets the `frameCounter` to the specified number of frames.
 *
 * @param framesCount The number of frames to set the counter to.
 */
#define setFrameCounter(framesCount) frameCounter = (framesCount)

/**
 * @brief Resets the frame counter to zero.
 *
 * This macro resets the `frameCounter` to zero, usually used to start counting
 * from scratch or to mark the beginning of a new measurement period.
 */
#define resetFrameCounter() setFrameCounter(0)

#endif