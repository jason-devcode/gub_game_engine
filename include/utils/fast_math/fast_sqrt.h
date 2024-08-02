#ifndef FAST_SQRT_H
#define FAST_SQRT_H

#include "fast_inv_sqrt.h" // For fast inverse square root

/**
 * @brief Computes the fast square root of a number.
 *
 * This macro uses the fast inverse square root function to compute the square root quickly.
 *
 * @param number The number for which the square root is to be computed.
 * @return The fast square root of the input number.
 */
#define fast_sqrt(number) (1.0 / fast_inv_sqrt(number))

#endif