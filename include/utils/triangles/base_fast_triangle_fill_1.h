#ifndef FAST_FILL_TRIANGLE_H
#define FAST_FILL_TRIANGLE_H

#include "../../engine_properties/screen_dimensions.h"
#include "../../engine_properties/framebuffer.h"

#include "../pixel.h"
#include "../swap.h"

#include <stdint.h>

static inline void fast_drawTriangleFill(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
    // correct Y order points
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

    if (y3 < 0 || gScreenHeight < y1)
        return; // protect top and bottom screen sides

    int DY_AB = y2 - y1;
    int DY_BC = y3 - y2;
    int DY_AC = y3 - y1;

    int DX_AB = x2 - x1;
    int DX_BC = x3 - x2;
    int DX_AC = x3 - x1;

    double slopeLeftX = (double)(DX_AB) / (double)(DY_AB + !DY_AB);
    double slopeRightX = (double)(DX_AC) / (double)(DY_AC + !DY_AC);

    double slopeLeftXBC = (double)(DX_BC) / (double)(DY_BC + !DY_BC);
    double slopeRightXBC = slopeRightX;

    if (slopeLeftX > slopeRightX)
    {
        swap_values(slopeLeftX, slopeRightX, double);
        swap_values(slopeLeftXBC, slopeRightXBC, double);
    }

    double xLeft, xRight;
    xLeft = xRight = x1;

top_triangle:
    goto check_first_iteration;
    do
    {
        int tempLeftX = xLeft;
        do
        {
            pixel(tempLeftX, y1, color);
        } while (++tempLeftX <= xRight);
    check_first_iteration:
        xLeft += slopeLeftX;
        xRight += slopeRightX;
    } while (++y1 < y2);

bottom_triangle:
    do
    {
        int tempLeftX = xLeft - 1;
        do
        {
            pixel(tempLeftX, y1, color);
        } while (++tempLeftX <= xRight);
        xLeft += slopeLeftXBC;
        xRight += slopeRightXBC;
    } while (++y1 < y3);
}

#endif