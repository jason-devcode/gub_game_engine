#ifndef CUT_TRIANGLE_H
#define CUT_TRIANGLE_H

#include <stdint.h>
#include "../../engine_properties/screen_dimensions.h"
#include "../swap.h"
#include "fast_triangle_fill.h"
#include "../geometry.h"

#define MAX_POLYGON_POINTS 10
#define EDGES_COUNT 4 // LEFT -> TOP -> RIGHT -> BOTTOM

typedef struct Point2D
{
    int x, y;
} Point2D;

void clippingLeftScreenSide(Point2D *points, int *count)
{
    Point2D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point2D current = points[i];
        Point2D next = points[(i + 1) % *count];

        if (current.x >= 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.x >= 100) != (next.x >= 100))
        {
            int x = 100;
            int y = current.y + (next.y - current.y) * (x - current.x) / (next.x - current.x);
            newPoints[newCount++] = (Point2D){x, y};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingRightScreenSide(Point2D *points, int *count)
{
    Point2D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point2D current = points[i];
        Point2D next = points[(i + 1) % *count];

        if (current.x <= gScreenWidth - 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.x <= gScreenWidth - 100) != (next.x <= gScreenWidth - 100))
        {
            int x = gScreenWidth - 100;
            int y = current.y + (next.y - current.y) * (x - current.x) / (next.x - current.x);
            newPoints[newCount++] = (Point2D){x, y};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingTopScreenSide(Point2D *points, int *count)
{
    Point2D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point2D current = points[i];
        Point2D next = points[(i + 1) % *count];

        if (current.y >= 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.y >= 100) != (next.y >= 100))
        {
            int y = 100;
            int x = current.x + (next.x - current.x) * (y - current.y) / (next.y - current.y);
            newPoints[newCount++] = (Point2D){x, y};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void clippingBottomScreenSide(Point2D *points, int *count)
{
    Point2D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point2D current = points[i];
        Point2D next = points[(i + 1) % *count];

        if (current.y <= gScreenHeight - 100)
        {
            newPoints[newCount++] = current;
        }

        if ((current.y <= gScreenHeight - 100) != (next.y <= gScreenHeight - 100))
        {
            int y = gScreenHeight - 100;
            int x = current.x + (next.x - current.x) * (y - current.y) / (next.y - current.y);
            newPoints[newCount++] = (Point2D){x, y};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void (*clippingSideFunctions[EDGES_COUNT])(Point2D *points, int *count) = {
    clippingLeftScreenSide,
    clippingTopScreenSide,
    clippingRightScreenSide,
    clippingBottomScreenSide};

void drawtriangleScreenClipping(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
    if (y1 > y2)
    {
        fast_swap_bitwise(x1, x2);
        fast_swap_bitwise(y1, y2);
    }
    if (y1 > y3)
    {
        fast_swap_bitwise(x1, x3);
        fast_swap_bitwise(y1, y3);
    }
    if (y2 > y3)
    {
        fast_swap_bitwise(x2, x3);
        fast_swap_bitwise(y2, y3);
    }

    if (gScreenHeight < y1 || y3 < 0)
        return; // protect top and bottom screen sides

    int currentPointsCount = 3; // initial polygon points

    Point2D points[MAX_POLYGON_POINTS] = {
        {x1, y1}, {x2, y2}, {x3, y3}};

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
        drawFilledTriangleGradient(
            points[0].x, points[0].y,
            points[(pointsIterator) % currentPointsCount].x,
            points[(pointsIterator) % currentPointsCount].y,
            points[(pointsIterator + 1) % currentPointsCount].x,
            points[(pointsIterator + 1) % currentPointsCount].y,
            color, color, color);
    } while (++pointsIterator < currentPointsCount);
}

#endif
