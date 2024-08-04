#ifndef CLAMP_UTILS_H
#define CLAMP_UTILS_H

/**
 * @brief Clamp a value to a specified range.
 *
 * Ensures the value stays within the specified minimum and maximum range.
 * If the value is less than the minimum, it returns the minimum.
 * If the value is greater than the maximum, it returns the maximum.
 * Otherwise, it returns the value itself.
 *
 * @param value The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
#define clampValue(value, min, max) ((value < min) ? min : ((value > max) ? max : value))

#endif // CLAMP_UTILS_H
