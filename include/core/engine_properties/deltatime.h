#ifndef DELTATIME_H
#define DELTATIME_H

/**
 * @brief Holds the delta time value.
 *
 * This variable stores the time difference between the current and previous frames, typically in seconds.
 * It is used for interpolating changes between frames to ensure smooth transitions and animations.
 */
static double deltatime = 0.0;

/**
 * @brief Retrieves the current delta time value.
 *
 * This macro returns the value of the `deltatime` variable.
 *
 * @return The current delta time, typically in seconds, used for frame-based interpolation.
 */
#define getDeltatime() deltatime

/**
 * @brief Calculates the delta time between two time points.
 *
 * This macro computes the difference between `currentTime` and `previousTime`, and converts it to seconds.
 * The calculated delta time is used for interpolating changes and animations between frames.
 *
 * @param currentTime The current time value, usually obtained from a time function.
 * @param previousTime The previous time value, from the last frame.
 * @return The calculated delta time in seconds.
 */
#define calculateDeltatime(currentTime, previousTime) (((double)(currentTime - previousTime)) / 1000.0)

#endif
