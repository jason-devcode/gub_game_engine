#ifndef TIMERS_API_HANDLER_SAMPLE_H
#define TIMERS_API_HANDLER_SAMPLE_H

#include "../../engine_properties/deltatime.h"
#include "../../engine_properties/previous_time.h"
#include "../../engine_properties/current_time.h"
#include "../../engine_properties/frame_counter.h"
#include "../../engine_properties/fps.h"

/**
 * @brief Initializes the timers.
 *
 * This function sets up any necessary resources or configurations for the timers.
 */
static inline void initializeTimers() {}

/**
 * @brief Updates the timers.
 *
 * This function should be called regularly to update the state of all active timers.
 */
static inline void updateTimers() {}

/**
 * @brief Closes and cleans up the timers.
 *
 * This function releases any resources allocated for the timers.
 */
static inline void closeTimers() {}

#endif