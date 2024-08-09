#ifndef BASE_TRIANGLE_DEPTH_TEST
#define BASE_TRIANGLE_DEPTH_TEST

#include "../swap.h"
#include "../color.h"
#include "../pixel.h"

/**
 * @brief Renders a filled triangle with depth testing, interpolating the z-coordinate 
 *        across the triangle surface.
 *
 * This function draws a filled triangle defined by the vertices (x1, y1, z1), 
 * (x2, y2, z2), and (x3, y3, z3) using the specified color. The function performs 
 * depth testing at each pixel to ensure that only the closest surfaces are rendered. 
 * It uses linear interpolation to compute the z-coordinate for each pixel, providing 
 * a more accurate representation of 3D surfaces.
 *
 * @param x1 The x-coordinate of the first vertex.
 * @param y1 The y-coordinate of the first vertex.
 * @param z1 The z-coordinate of the first vertex.
 * @param x2 The x-coordinate of the second vertex.
 * @param y2 The y-coordinate of the second vertex.
 * @param z2 The z-coordinate of the second vertex.
 * @param x3 The x-coordinate of the third vertex.
 * @param y3 The y-coordinate of the third vertex.
 * @param z3 The z-coordinate of the third vertex.
 * @param color The color used to draw the triangle.
 *
 * @note The vertices of the triangle are sorted by their y-coordinates before 
 *       rendering to simplify the triangle rasterization process. The triangle is 
 *       divided into a top and bottom part, which are rendered separately.
 *
 * @note The function uses depth testing through the `pixelDepthTest` function, 
 *       which is expected to be defined elsewhere. The z-values are interpolated 
 *       across the triangle's surface to determine which pixels should be rendered.
 *
 * @note To prevent division by zero errors during slope calculations, small adjustments 
 *       are made when the difference between coordinates is zero.
 *
 * @note The function contains two main loops for rendering the upper and lower parts 
 *       of the triangle. These loops interpolate both x and z values for each scanline.
 *
 * @warning The function assumes that the vertices provided form a valid triangle. 
 *          Degenerate triangles, where all points are collinear, may not be handled correctly.
 */
void baseTriangleDepthTest(int x1, int y1, double z1, int x2, int y2, double z2, int x3, int y3, double z3, uint32_t color)
{
    if (y1 > y2)
    {
        swap_values(x1, x2, int);
        swap_values(y1, y2, int);
        swap_values(z1, z2, double);
    }
    if (y1 > y3)
    {
        swap_values(x1, x3, int);
        swap_values(y1, y3, int);
        swap_values(z1, z3, double);
    }
    if (y2 > y3)
    {
        swap_values(x2, x3, int);
        swap_values(y2, y3, int);
        swap_values(z2, z3, double);
    }

    // Triángulo superior
    double DY_AB = y2 - y1;
    double DY_AC = y3 - y1;
    double DY_BC = y3 - y2;

    double DX_AB = x2 - x1;
    double DX_AC = x3 - x1;
    double DX_BC = x3 - x2;

    double DZ_AB = z2 - z1;
    double DZ_AC = z3 - z1;
    double DZ_BC = z3 - z2;

    double slopeLeftAB = DX_AB / (DY_AB + !DY_AB);
    double slopeLeftBC = DX_BC / (DY_BC + !DY_BC);
    double slopeRightAC = DX_AC / (DY_AC + !DY_AC);
    double slopeRightAC2 = slopeRightAC;

    double slopeZLeftAB = DZ_AB / (DY_AB + !DY_AB);

    double slopeZLeftBC = DZ_BC / (DY_BC + !DY_BC);
    double slopeZRightAC = DZ_AC / (DY_AC + !DY_AC);
    double slopeZRightAC2 = slopeZRightAC;

    double xLeft = x1, xRight = x1;
    double zLeft = z1, zRight = z1;

    if (DY_AB == 0)
    {
        xLeft = x2;
        zLeft = z2;
    }

    if (slopeLeftAB > slopeRightAC)
    {
        swap_values(slopeLeftAB, slopeRightAC, double);
        swap_values(slopeZLeftAB, slopeZRightAC, double);
    }

    if (xRight < xLeft)
    {
        swap_values(xLeft, xRight, double);
        swap_values(zLeft, zRight, double);
    }

    // pixelDepthTest(xLeft, y1, z1, color);
    goto first_triangle_iteration;
top_triangle:
    do
    {
        xLeft += slopeLeftAB;
        xRight += slopeRightAC;
        zLeft += slopeZLeftAB;
        zRight += slopeZRightAC;

        double tempLeftX = xLeft;
        double tempZ = zLeft;
        double DX = (xRight - xLeft);
        double zSlope = (zRight - zLeft) / (DX + !DX);
        do
        {
            // pixelDepthTest(tempLeftX, y1, tempZ, color);
            // pixelDepthTest(tempLeftX, y1, tempZ, RGB(255, 0, (int)(tempZ * 255)));
            pixelDepthTest(tempLeftX, y1, tempZ, RGB((int)(tempZ * 255), (int)(tempZ * 255), (int)(tempZ * 255)));

            tempZ += zSlope;
        } while (++tempLeftX <= xRight);
    first_triangle_iteration:
    } while (++y1 <= y2);

bottom_triangle:
    if (slopeLeftBC < slopeRightAC2)
    {
        swap_values(slopeLeftBC, slopeRightAC2, double);
        swap_values(slopeZLeftBC, slopeZRightAC2, double);
    }
    y1 = y2;

    do
    {
        double tempLeftX = xLeft;
        double tempZ = zLeft;
        double DX = (xRight - xLeft);
        double zSlope = (zRight - zLeft) / (DX + !DX);
        do
        {
            pixelDepthTest(tempLeftX, y1, tempZ, RGB((int)(tempZ * 255), (int)(tempZ * 255), (int)(tempZ * 255)));
            // pixelDepthTest(tempLeftX, y1, tempZ, RGB((int)(tempZ * 255), 0, 0));
            // pixelDepthTest(tempLeftX, y1, tempZ, color);
            tempZ += zSlope;
        } while (++tempLeftX <= xRight);
        xLeft += slopeLeftBC;
        xRight += slopeRightAC2;
        zLeft += slopeZLeftBC;
        zRight += slopeZRightAC2;
    } while (++y1 < y3);
}

#endif