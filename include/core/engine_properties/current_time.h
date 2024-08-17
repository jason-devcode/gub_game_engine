#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

#include <stdint.h>

/**
 * @brief Holds the current time value.
 *
 * This variable stores the current time in milliseconds.
 */
static uint32_t currentTime = 0;

/**
 * @brief Sets the current time value.
 *
 * This macro sets the value of the `currentTime` variable.
 *
 * @param time_value The time value to be set, typically in milliseconds.
 */
#define setCurrenTime(time_value) currentTime = (time_value)

#endif