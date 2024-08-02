#ifndef FAST_ABS_H
#define FAST_ABS_H

/**
 * @file fast_abs.h
 * @brief Defines a macro for computing absolute values quickly.
 *
 * Provides a macro `fast_abs` to compute the absolute value of a number with minimal overhead.
 */

/**
 * @brief Computes the absolute value of a number.
 *
 * Returns the absolute value of `x` by checking if `x` is negative and negating it if necessary.
 *
 * @param x The number to compute the absolute value of.
 * @return The absolute value of `x`.
 */
#define fast_abs(x) ((x) < 0 ? -(x) : (x))

#endif // FAST_ABS_H