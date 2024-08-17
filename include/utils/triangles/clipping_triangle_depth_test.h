#ifndef CUT_TRIANGLE_H
#define CUT_TRIANGLE_H

#include "../swap.h"
#include "./fast_triangle_zbuffer.h"

#include "../../core/engine_properties/screen_dimensions.h"

#include <stdint.h>

#define MAX_POLYGON_POINTS 10
#define EDGES_COUNT 6 // LEFT -> TOP -> RIGHT -> BOTTOM -> NEAR -> FAR

typedef struct Point3D
{
    double x, y, z;
} Point3D;

#define CLIP_REGION 0

void clippingLeftScreenSide(Point3D *points, int *count)
{
    Point3D newPoints[MAX_POLYGON_POINTS];
    int newCount = 0;

    for (int i = 0; i < *count; i++)
    {
        Point3D current = points[i];
        Point3D next = points[(i + 1) % *count];

        if (current.x >= CLIP_REGION)
        {
            newPoints[newCount++] = current;
        }

        if ((current.x >= CLIP_REGION) != (next.x >= CLIP_REGION))
        {
            double x = CLIP_REGION;
            double y = current.y + (next.y - current.y) * (x - current.x) / (next.x - current.x);
            double z = current.z + (next.z - current.z) * (x - current.x) / (next.x - current.x);
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

        if (current.x <= gScreenWidth - CLIP_REGION)
        {
            newPoints[newCount++] = current;
        }

        if ((current.x <= gScreenWidth - CLIP_REGION) != (next.x <= gScreenWidth - CLIP_REGION))
        {
            double x = gScreenWidth - CLIP_REGION;
            double y = current.y + (next.y - current.y) * (x - current.x) / (next.x - current.x);
            double z = current.z + (next.z - current.z) * (x - current.x) / (next.x - current.x);
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

        if (current.y >= CLIP_REGION)
        {
            newPoints[newCount++] = current;
        }

        if ((current.y >= CLIP_REGION) != (next.y >= CLIP_REGION))
        {
            double y = CLIP_REGION;
            double x = current.x + (next.x - current.x) * (y - current.y) / (next.y - current.y);
            double z = current.z + (next.z - current.z) * (y - current.y) / (next.y - current.y);
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

        if (current.y <= gScreenHeight - CLIP_REGION)
        {
            newPoints[newCount++] = current;
        }

        if ((current.y <= gScreenHeight - CLIP_REGION) != (next.y <= gScreenHeight - CLIP_REGION))
        {
            double y = gScreenHeight - CLIP_REGION;
            double x = current.x + (next.x - current.x) * (y - current.y) / (next.y - current.y);
            double z = current.z + (next.z - current.z) * (y - current.y) / (next.y - current.y);
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
    double near = 0.25; // near plane distance

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
            double x = current.x + (next.x - current.x) * (near - current.z) / (next.z - current.z);
            double y = current.y + (next.y - current.y) * (near - current.z) / (next.z - current.z);
            double z = near; // Intersection point on the near plane

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
    double far = 40; // far plane distance

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
            double z = far;
            double x = current.x + (next.x - current.x) * (z - current.z) / (next.z - current.z);
            double y = current.y + (next.y - current.y) * (z - current.z) / (next.z - current.z);
            newPoints[newCount++] = (Point3D){x, y, z};
        }
    }

    *count = newCount;
    for (int i = 0; i < newCount; i++)
    {
        points[i] = newPoints[i];
    }
}

void drawTriangleScreenClippingXYZ(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, uint32_t color)
{

    // if (gScreenHeight < y1 || y3 < 0)
    // {
    //     return; // protect top and bottom screen sides
    // }
    int currentPointsCount = 3; // initial polygon points

    Point3D points[MAX_POLYGON_POINTS] = {
        {x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3}};

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
        Point3D *pointA = &points[0];
        Point3D *pointB = &points[(pointsIterator) % currentPointsCount];
        Point3D *pointC = &points[(pointsIterator + 1) % currentPointsCount];

        double projAx = pointA->x / pointA->z;
        double projAy = pointA->y / pointA->z;

        double projBx = pointB->x / pointB->z;
        double projBy = pointB->y / pointB->z;

        double projCx = pointC->x / pointC->z;
        double projCy = pointC->y / pointC->z;

        fast_TriangleDepthTest(
            pointA->x, pointA->y, pointA->z / 20,
            pointB->x, pointB->y, pointB->z / 20,
            pointC->x, pointC->y, pointC->z / 20,
            color);

        drawTriangleWireDepthTest(
            pointA->x, pointA->y, pointA->z / 20 - 0.002,
            pointB->x, pointB->y, pointB->z / 20 - 0.002,
            pointC->x, pointC->y, pointC->z / 20 - 0.002,
            0xFFFF00);

    } while (++pointsIterator < currentPointsCount);
}

void drawTriangleScreenClippingDepthTest(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, uint32_t color)
{
    int currentPointsCount = 3; // initial polygon points

    Point3D points[MAX_POLYGON_POINTS] = {
        {x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3}};

    clippingNearScreenSide(points, &currentPointsCount);
    if (currentPointsCount < 3)
        return; // No points left after clipping
    clippingFarScreenSide(points, &currentPointsCount);
    if (currentPointsCount == 0)
        return; // No points left after clipping

    int pointsIterator = 1;

    double Zconst = 1;

    do
    {
        Point3D *pointA = &points[0];
        Point3D *pointB = &points[(pointsIterator) % currentPointsCount];
        Point3D *pointC = &points[(pointsIterator + 1) % currentPointsCount];

        if (pointA->z <= 0 || pointB->z <= 0 || pointC->z <= 0)
            continue;

        double projAx = (pointA->x) / (pointA->z);
        double projAy = (pointA->y) / (pointA->z);

        double projBx = (pointB->x) / (pointB->z);
        double projBy = (pointB->y) / (pointB->z);

        double projCx = (pointC->x) / (pointC->z);
        double projCy = (pointC->y) / (pointC->z);

        drawTriangleScreenClippingXYZ(
            floor(projAx * gHalfScreenWidth) + gHalfScreenWidth + 0.5, floor(projAy * -gHalfScreenHeight) + gHalfScreenHeight + 0.5, pointA->z,
            floor(projBx * gHalfScreenWidth) + gHalfScreenWidth + 0.5, floor(projBy * -gHalfScreenHeight) + gHalfScreenHeight + 0.5, pointB->z,
            floor(projCx * gHalfScreenWidth) + gHalfScreenWidth + 0.5, floor(projCy * -gHalfScreenHeight) + gHalfScreenHeight + 0.5, pointC->z,
            color);

    } while (++pointsIterator < currentPointsCount);
}

#endif