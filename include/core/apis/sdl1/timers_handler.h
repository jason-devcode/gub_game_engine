#ifndef TIMERS_HANDLER_SDL_1_H
#define TIMERS_HANDLER_SDL_1_H

#include <SDL/SDL_timer.h>

#include "../../engine_properties/deltatime.h"
#include "../../engine_properties/previous_time.h"
#include "../../engine_properties/current_time.h"
#include "../../engine_properties/frame_counter.h"
#include "../../engine_properties/fps.h"

/**
 * @brief Initializes the timers.
 *
 * This function sets up the initial state for the timers, including setting
 * the current and previous time, starting the FPS counter, and resetting
 * the frame counter.
 */
static inline void initializeTimers()
{
    setCurrenTime(SDL_GetTicks());
    setPreviousTime(SDL_GetTicks());
    setFpsStartTime(SDL_GetTicks());
    setFrameCounter(0);
    setFpsCounter(0);
}

/**
 * @brief Updates the timers.
 *
 * This function updates the frame counter, calculates the delta time, and
 * updates the FPS counter. It calculates the time elapsed since the last
 * frame and updates the FPS count every second.
 */
static inline void updateTimers()
{
    updateFrameCounter();
    setCurrenTime(SDL_GetTicks());

    deltatime = calculateDeltatime(currentTime, previousTime);

    setPreviousTime(currentTime);

    // Update FPS in seconds
    if ((currentTime - fpsStartTime) > 999)
    {
        fpsCounter = frameCounter;
        resetFrameCounter();
        fpsStartTime = currentTime;
    }
}

/**
 * @brief Closes and cleans up the timers.
 *
 * This function resets the timer-related variables to zero, effectively
 * cleaning up the state used for timekeeping.
 */
static inline void closeTimers()
{
    setCurrenTime(0);
    setPreviousTime(0);
    setFpsStartTime(0);
    setFrameCounter(0);
    setFpsCounter(0);
}

#endif