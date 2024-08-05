#ifndef FAST_MIN_MAX_H
#define FAST_MIN_MAX_H

/**
 * @brief Returns the minimum of two values.
 *
 * This macro compares two values and returns the smaller value.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @return The smaller of the two values.
 */
#define get_min_value(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief Returns the maximum of two values.
 *
 * This macro compares two values and returns the larger value.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @return The larger of the two values.
 */
#define get_max_value(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Returns the minimum of three values.
 *
 * This macro compares three values and returns the smallest value.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @param c Third value to compare.
 * @return The smallest of the three values.
 */
#define get_min_value_of_three(a, b, c) (get_min_value(get_min_value(a, b), c))

/**
 * @brief Returns the maximum of three values.
 *
 * This macro compares three values and returns the largest value.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @param c Third value to compare.
 * @return The largest of the three values.
 */
#define get_max_value_of_three(a, b, c) (get_max_value(get_max_value(a, b), c))

#endif // FAST_MIN_MAX_H