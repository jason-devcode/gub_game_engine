#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <stdint.h>

/**
 * @brief Holds the frame per second (FPS) count.
 *
 * This variable stores the number of frames per second that have been rendered.
 * It is updated periodically to provide information on the rendering performance.
 */
static uint32_t fpsCounter = 0;

/**
 * @brief Holds the start time for FPS calculation.
 *
 * This variable stores the time when the FPS calculation period starts.
 * It is used to measure the elapsed time over which frames are counted.
 */
static uint32_t fpsStartTime = 0;

/**
 * @brief Sets the frame per second (FPS) count.
 *
 * This macro sets the `fpsCounter` to the specified number of frames per second.
 *
 * @param frames_per_second_count The number of frames per second to set.
 */
#define setFpsCounter(frames_per_second_count) fpsCounter = frames_per_second_count

/**
 * @brief Sets the start time for FPS calculation.
 *
 * This macro sets the `fpsStartTime` to the given start time. This is typically used to mark
 * the beginning of a new period for FPS calculation.
 *
 * @param startTime The start time for the FPS calculation period.
 */
#define setFpsStartTime(startTime) fpsStartTime = (startTime)

/**
 * @brief Retrieves the current frame per second (FPS) count.
 *
 * This macro returns the value of the `fpsCounter` variable, which represents the current
 * number of frames per second.
 *
 * @return The current frame per second count.
 */
#define getFps() fpsCounter

#endif