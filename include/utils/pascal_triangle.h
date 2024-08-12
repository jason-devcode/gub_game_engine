#ifndef PASCAL_TRIANGLE_GENERATOR_H
#define PASCAL_TRIANGLE_GENERATOR_H

#include <stdlib.h>

/**
 * @brief Creates Pascal's Triangle up to a specified row.
 *
 * This function allocates and returns a 2D array representing Pascal's Triangle
 * up to the specified maximum row (maxRow). Each row in Pascal's Triangle
 * contains binomial coefficients.
 *
 * @param maxRow The maximum row number in Pascal's Triangle to compute.
 * @return A pointer to a 2D array containing Pascal's Triangle.
 *         The caller is responsible for freeing this memory using freePascalTriangle.
 */
static inline int **createPascalTriangle(int maxRow)
{
    int **pascalTriangle = (int **)malloc((maxRow + 1) * sizeof(int *));
    if (!pascalTriangle)
    {
        return NULL; // Return NULL if memory allocation fails
    }

    for (int currentRow = 0; currentRow <= maxRow; ++currentRow)
    {
        pascalTriangle[currentRow] = (int *)malloc((currentRow + 1) * sizeof(int));
        if (!pascalTriangle[currentRow])
        {
            // Free previously allocated memory if allocation fails
            for (int previousRow = 0; previousRow < currentRow; ++previousRow)
                free(pascalTriangle[previousRow]);
            free(pascalTriangle);
            return NULL;
        }

        // The first and last elements of each row are always 1
        pascalTriangle[currentRow][0] = pascalTriangle[currentRow][currentRow] = 1;

        // Calculate the inner elements of the row
        for (int column = 1; column < currentRow; ++column)
            pascalTriangle[currentRow][column] = pascalTriangle[currentRow - 1][column - 1] + pascalTriangle[currentRow - 1][column];
    }

    return pascalTriangle;
}

/**
 * @brief Frees the memory allocated for Pascal's Triangle.
 *
 * This function frees the memory allocated by createPascalTriangle.
 *
 * @param pascalTriangle A pointer to the 2D array containing Pascal's Triangle.
 * @param maxRow The maximum row number in Pascal's Triangle that was allocated.
 */
static inline void freePascalTriangle(int **pascalTriangle, int maxRow)
{
    for (int currentRow = 0; currentRow <= maxRow; ++currentRow)
        free(pascalTriangle[currentRow]);
    free(pascalTriangle);
}

#endif
