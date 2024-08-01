/**
 * @file timers.h
 * @brief Header file for time management and FPS calculation utilities.
 *
 * This file provides functionality to manage time intervals, calculate frames per second (FPS),
 * and handle performance tracking. It includes functions and macros for time management
 * and FPS calculations used in rendering and game loops.
 */

#ifndef TIMERS_H
#define TIMERS_H

#include <time.h>   // For clock_t type and time functions
#include <unistd.h> // For usleep microseconds suspend execution function

/**
 * @var deltatime
 * @brief Time interval in seconds since the last update.
 *
 * This variable holds the amount of time that has passed since the last update, used to compute
 * smooth animations and time-based logic.
 */
double deltatime = 0.0;

/**
 * @var lastSecond
 * @brief Timestamp of the last second update.
 *
 * This variable stores the last timestamp when the second-based update occurred, used for
 * FPS calculation.
 */
double lastSecond = 0.0;

/**
 * @var lastTime
 * @brief Timestamp of the last render update.
 *
 * This variable stores the last timestamp when the render update occurred, used to calculate
 * the elapsed time between updates.
 */
double lastTime = 0.0;

/**
 * @var fpsCounter
 * @brief Counter for the number of frames since the last second.
 *
 * This variable counts the number of frames that have been rendered since the last second update.
 */
int fpsCounter = 0;

/**
 * @var lastFpsCounter
 * @brief FPS count from the last second.
 *
 * This variable holds the number of frames per second counted during the last second.
 */
int lastFpsCounter = 0;

/**
 * @brief Get the current time in milliseconds.
 *
 * This function retrieves the current time in milliseconds using `clock_gettime`.
 *
 * @return The current time in milliseconds.
 */
long current_time_millis()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

/**
 * @brief Get the current time in seconds.
 *
 * This function retrieves the current time in seconds since the epoch. It uses `clock_gettime`
 * with `CLOCK_REALTIME` to provide the current wall-clock time.
 *
 * @return The current time in seconds.
 */
double current_time_seconds()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
}

/**
 * @brief Calculates the elapsed time in seconds between two timestamps.
 *
 * This function computes the time difference in seconds between two timestamps.
 *
 * @param start The start timestamp in seconds.
 * @param end The end timestamp in seconds.
 * @return The elapsed time in seconds between `start` and `end`.
 */
double elapsed_time(double start, double end)
{
    return end - start;
}

/**
 * @brief Convert milliseconds to seconds.
 *
 * This function converts a time value from milliseconds to seconds.
 *
 * @param milliseconds The time value in milliseconds.
 * @return The time value in seconds.
 */
double millis_to_seconds(long milliseconds)
{
    return milliseconds / 1000.0;
}

/**
 * @brief Convert seconds to milliseconds.
 *
 * This function converts a time value from seconds to milliseconds.
 *
 * @param seconds The time value in seconds.
 * @return The time value in milliseconds.
 */
long seconds_to_millis(double seconds)
{
    return (long)(seconds * 1000.0);
}

/**
 * @brief Macro to update time-related variables and FPS counter.
 *
 * This macro updates the `deltatime`, FPS counter, and the last time variables. It should be called
 * once per frame to ensure accurate time tracking and FPS calculation. It uses `current_time_seconds()`
 * to calculate the time intervals for more precise timing.
 */
#define UPDATE_TIMERS()                              \
    double currentTime = current_time_seconds();     \
    deltatime = elapsed_time(lastTime, currentTime); \
    if ((currentTime - lastSecond) > 1.0)            \
    {                                                \
        lastSecond = currentTime;                    \
        lastFpsCounter = fpsCounter;                 \
        fpsCounter = 0;                              \
    }                                                \
    ++fpsCounter;                                    \
    lastTime = currentTime

/**
 * @brief Get the FPS count from the last second.
 *
 * This macro returns the number of frames per second calculated during the last second.
 *
 * @return The FPS count from the last second.
 */
#define getFps() (lastFpsCounter)

/**
 * @brief Get the time interval in milliseconds.
 *
 * This macro returns the time interval since the last update in milliseconds.
 *
 * @return The time interval in milliseconds.
 */
#define getIntDeltatime() ((int)(deltatime * 1000.0))

/**
 * @brief Get the time interval in seconds.
 *
 * This macro returns the time interval since the last update in seconds.
 *
 * @return The time interval in seconds.
 */
#define getDeltatime() (deltatime)

/**
 * @brief Suspends the execution of the program for a specified number of milliseconds.
 *
 * This macro uses the usleep function to pause the execution of the program
 * for the given number of milliseconds. It is intended to be used to introduce
 * delays in the rendering process.
 *
 * @param milliseconds The number of milliseconds to suspend the execution.
 */
#define engineSleep(milliseconds) usleep(milliseconds * 1000)

/**
 * @brief Suspends the execution of the program for a specified number of milliseconds.
 *
 * This macro uses the usleep function to pause the execution of the program
 * for the given number of milliseconds. It is intended to be used to introduce
 * delays in the rendering process.
 *
 * @param milliseconds The number of milliseconds to suspend the execution.
 */
#define renderDelay(milliseconds) usleep(milliseconds * 1000)

#endif