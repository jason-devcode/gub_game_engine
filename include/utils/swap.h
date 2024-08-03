#ifndef SWAP_UTILS_H
#define SWAP_UTILS_H

/**
 * A macro to swap the values of two variables using bitwise XOR operations.
 * This method performs the swap without using a temporary variable and is
 * often used for its efficiency.
 *
 * @param a  The first variable to swap.
 * @param b  The second variable to swap.
 */
#define fast_swap_bitwise(a, b) \
    do                          \
    {                           \
        (a) ^= (b);             \
        (b) ^= (a);             \
        (a) ^= (b);             \
    } while (0)

#endif