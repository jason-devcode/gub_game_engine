#ifndef TIMERS_HANDLER_SDL_2_H
#define TIMERS_HANDLER_SDL_2_H

#include <SDL2/SDL_timer.h>

#include "../../engine_properties/deltatime.h"
#include "../../engine_properties/previous_time.h"
#include "../../engine_properties/current_time.h"
#include "../../engine_properties/frame_counter.h"
#include "../../engine_properties/fps.h"

/**
 * @brief Initializes the timer system.
 *
 * This function sets up the initial timer values for the current time, previous time,
 * FPS start time, frame counter, and FPS counter. It is called at the start of the game loop
 * or when the timer system is first initialized.
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
 * @brief Updates the timer values and calculates the delta time.
 *
 * This function updates the current time, calculates the time difference (delta time)
 * since the last update, and updates the frame counter and FPS counter. It also updates
 * the FPS count every second.
 */
static inline void updateTimers()
{
    updateFrameCounter();
    setCurrenTime(SDL_GetTicks());

    deltatime = calculateDeltatime(currentTime, previousTime);

    setPreviousTime(currentTime);

    // update fps in second
    if ((currentTime - fpsStartTime) > 999)
    {
        fpsCounter = frameCounter;
        resetFrameCounter();
        fpsStartTime = currentTime;
    }
}

/**
 * @brief Closes and cleans up the timer system.
 *
 * This function resets all timer-related values to zero, effectively closing down
 * the timer system. It is called when the game or application is shutting down.
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