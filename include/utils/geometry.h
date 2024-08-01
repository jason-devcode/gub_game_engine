#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>
#include "../prototypes/graphic_engine_prototypes.h"

// use r*r = x*x + y*y circle formula for find points inside the circle
void drawFilledCircle(int cx, int cy, int radius, uint32_t color)
{
    for (int Y = -radius; Y < radius; ++Y)
    {
        for (int X = -radius; X < radius; ++X)
        {
            if ((X * X + Y * Y) < radius * radius) // if the point is inside of the circle
            {
                pixel(X + cx, Y + cy, color);
            }
        }
    }
}

// use r*r = x*x + y*y circle formula for find points inside the circle
void drawCircle(int cx, int cy, int radius, int weight, uint32_t color)
{
    register int correctRadius = radius + (weight >> 1) + 1;
    for (int Y = -radius; Y < radius; ++Y)
    {
        for (int X = -radius; X < radius; ++X)
        {
            register unsigned int distance = (X * X + Y * Y);
            register int innerRadius = radius - (weight + 1);
            register int outRadius = radius;

            register unsigned int squareOutRadius = outRadius * outRadius;
            register unsigned int squareInnerRadius = innerRadius * innerRadius;

            if (distance > squareInnerRadius && distance < squareOutRadius)
                pixel(X + cx, Y + cy, color);
        }
    }
}

#endif