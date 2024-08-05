#ifndef ANALYTIC_GEOMETRY_UTILS_H
#define ANALYTIC_GEOMETRY_UTILS_H

/**
 * @brief Calculate the area of a parallelogram using vertex coordinates.
 *
 * @param x1 x-coordinate of the first vertex.
 * @param y1 y-coordinate of the first vertex.
 * @param x2 x-coordinate of the second vertex.
 * @param y2 y-coordinate of the second vertex.
 *
 * @return Area of the parallelogram.
 */
#define calculateParallelogramAreaFromCoords(x1, y1, x2, y2) \
    (((x1) * (y2)) - ((x2) * (y1)))

/**
 * @brief Calculate the area of a parallelogram using two points.
 *
 * @param A First point (x, y).
 * @param B Second point (x, y).
 *
 * @return Area of the parallelogram formed by the two points.
 */
#define calculateParallelogramAreaFromPoints(A, B) \
    calculateParallelogramAreaFromCoords((A).x, (A).y, (B).x, (B).y)

/**
 * @brief Calculate the area of a triangle using three points.
 *
 * @param A First point (x, y).
 * @param B Second point (x, y).
 * @param C Third point (x, y).
 *
 * @return Area of the triangle formed by the three points.
 */
#define calculateTriangleAreaFromPoints(A, B, C) \
    (calculateParallelogramAreaFromCoords((B).x - (A).x, (B).y - (A).y, (C).x - (A).x, (C).y - (A).y) / 2)

/**
 * @brief Calculate the area of a triangle using vertex coordinates.
 *
 * @param x1 x-coordinate of the first vertex.
 * @param y1 y-coordinate of the first vertex.
 * @param x2 x-coordinate of the second vertex.
 * @param y2 y-coordinate of the second vertex.
 * @param x3 x-coordinate of the third vertex.
 * @param y3 y-coordinate of the third vertex.
 *
 * @return Area of the triangle formed by the three vertices.
 */
#define calculateTriangleAreaFromCoords(x1, y1, x2, y2, x3, y3) \
    (calculateParallelogramAreaFromCoords((x2) - (x1), (y2) - (y1), (x3) - (x1), (y3) - (y1)) / 2)

#endif