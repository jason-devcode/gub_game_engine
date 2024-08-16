#ifndef PREVIOUS_TIME_H
#define PREVIOUS_TIME_H

#include <stdint.h>

/**
 * @brief Holds the timestamp of the previous frame or event.
 *
 * This variable stores the time value (in milliseconds) of the last recorded
 * frame or event, used to calculate the elapsed time between the previous
 * and current frame.
 */
static uint32_t previousTime = 0;

/**
 * @brief Sets the previous time to a specified value.
 *
 * This macro updates the `previousTime` variable to the provided time value.
 *
 * @param time_value The time value (in milliseconds) to set as the previous time.
 */
#define setPreviousTime(time_value) previousTime = (time_value)

#endif