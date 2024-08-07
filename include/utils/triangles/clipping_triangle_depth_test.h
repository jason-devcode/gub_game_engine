#ifndef CUT_TRIANGLE_H
#define CUT_TRIANGLE_H

#include <stdint.h>
#include "../../engine_properties/screen_dimensions.h"
#include "../swap.h"
#include "fast_triangle_fill.h"
#include "../geometry.h"

#define MAX_POLYGON_POINTS 10
#define EDGES_COUNT 6 // LEFT -> TOP -> RIGHT -> BOTTOM -> NEAR -> FAR

typedef struct Point3D
{
    int x, y, z;
} Point3D;

void clippingLeftScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.x >= 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.x >= 100) != (next.x >= 100))
        {
            int x = 100;
            int y = current.y + (next.y - current.y) * (x - current.x) / (next.x - current.x);
            int z = current.z + (next.z - current.z) * (x - current.x) / (next.x - current.x);
            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingRightScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.x <= gScreenWidth - 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.x <= gScreenWidth - 100) != (next.x <= gScreenWidth - 100))
        {
            int x = gScreenWidth - 100;
            int y = current.y + (next.y - current.y) * (x - current.x) / (next.x - current.x);
            int z = current.z + (next.z - current.z) * (x - current.x) / (next.x - current.x);
            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingTopScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.y >= 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.y >= 100) != (next.y >= 100))
        {
            int y = 100;
            int x = current.x + (next.x - current.x) * (y - current.y) / (next.y - current.y);
            int z = current.z + (next.z - current.z) * (y - current.y) / (next.y - current.y);
            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingBottomScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.y <= gScreenHeight - 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.y <= gScreenHeight - 100) != (next.y <= gScreenHeight - 100))
        {
            int y = gScreenHeight - 100;
            int x = current.x + (next.x - current.x) * (y - current.y) / (next.y - current.y);
            int z = current.z + (next.z - current.z) * (y - current.y) / (next.y - current.y);
            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingNearScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;
    int near = 0; // near plane distance

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.z >= near)
        {
            newPoints[newCount++] = current;
        }

        if ((current.z >= near) != (next.z >= near))
        {
            // Calculate intersection point with near plane
            int x = current.x + (next.x - current.x) * (near - current.z) / (next.z - current.z);
            int y = current.y + (next.y - current.y) * (near - current.z) / (next.z - current.z);
            int z = near; // Intersection point on the near plane

            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingFarScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;
    int far = 1000; // far plane distance

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.z <= far)
        {
            newPoints[newCount++] = current;
        }

        if ((current.z <= far) != (next.z <= far))
        {
            int z = far;
            int x = current.x + (next.x - current.x) * (z - current.z) / (next.z - current.z);
            int y = current.y + (next.y - current.y) * (z - current.z) / (next.z - current.z);
            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void (*clippingSideFunctions[EDGES_COUNT])(Point3D *points, int *count) = {
    clippingLeftScreenSide,
    clippingTopScreenSide,
    clippingRightScreenSide,
    clippingBottomScreenSide,
    clippingNearScreenSide,
    clippingFarScreenSide};

void drawTriangleScreenClippingDepthTest(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, uint32_t color)
{
    if (y1 > y2)
    {
        fast_swap_bitwise(x1, x2);
        fast_swap_bitwise(y1, y2);
        fast_swap_bitwise(z1, z2);
    }
    if (y1 > y3)
    {
        fast_swap_bitwise(x1, x3);
        fast_swap_bitwise(y1, y3);
        fast_swap_bitwise(z1, z3);
    }
    if (y2 > y3)
    {
        fast_swap_bitwise(x2, x3);
        fast_swap_bitwise(y2, y3);
        fast_swap_bitwise(z2, z3);
    }

    if (gScreenHeight < y1 || y3 < 0)
    {
        return; // protect top and bottom screen sides
    }

    int currentPointsCount = 3; // initial polygon points

    Point3D points[MAX_POLYGON_POINTS] = {
        {x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3}};

    clippingNearScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping
    clippingFarScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping
    clippingLeftScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping
    clippingTopScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping
    clippingRightScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping
    clippingBottomScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping

    int pointsIterator = 1;
    do
    {
        drawFilledTriangleGradientDepthTest(
            points[0].x, points[0].y, points[0].z,
            points[(pointsIterator) % currentPointsCount].x,
            points[(pointsIterator) % currentPointsCount].y,
            points[(pointsIterator) % currentPointsCount].z,
            points[(pointsIterator + 1) % currentPointsCount].x,
            points[(pointsIterator + 1) % currentPointsCount].y,
            points[(pointsIterator + 1) % currentPointsCount].z,
            0xFFFF0000, 0xFF00FF00, 0xFF0000FF);
    } while (++pointsIterator < currentPointsCount);
}

#endif