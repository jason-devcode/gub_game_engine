#include "../include/game_engine.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/raster.h"
#include "../include/utils/geometry.h"
#include "../include/utils/analytic_geometry.h"
#include "../include/utils/gamma.h"
#include "../include/utils/vectorial_2D.h"
#include "../include/utils/cartesian_2D.h"
#include "../include/utils/triangles/fast_triangle_fill.h"

Vec2f mouseCartesianPosition = {0, 0};

Vec2f parallelogramPoints[2] = {
    {.x = 4, .y = 0},
    {.x = 4, .y = 4}};

Vec2f trianglePoints[] = {{0, 0}, {640, 0}, {0, 640}};

#define draw_info()                                                                                                                        \
    drawFormattedText(                                                                                                                     \
        10, 10, 0xFFFFFF00,                                                                                                                \
        "FPS: %d\ndeltatime: %lf\nmouse screen position: ( %d, %d )\nmouse cartesian position: ( %0.2lf, %0.2lf )\narea triangle: %0.2lf", \
        getFps(), getDeltatime(),                                                                                                          \
        GET_MOUSE_X(), GET_MOUSE_Y(),                                                                                                      \
        mouseCartesianPosition.x, mouseCartesianPosition.y,                                                                                \
        calculateTriangleAreaFromPoints(trianglePoints[0], trianglePoints[1], trianglePoints[2]))

void onMouseMotion()
{
    mouseCartesianPosition.x = convertScreenXToCartesian2DX(GET_MOUSE_X());
    mouseCartesianPosition.y = convertScreenYToCartesian2DY(GET_MOUSE_Y());
}

void onMouseLeftClickDownParallelogram()
{
    const double MOVE_ZONE = 0.5;
    for (int i = 0; i < 2; ++i)
    {
        Vec2f *point = &parallelogramPoints[i];

        if (mouseCartesianPosition.x > point->x - MOVE_ZONE && mouseCartesianPosition.x < point->x + MOVE_ZONE &&
            mouseCartesianPosition.y > point->y - MOVE_ZONE && mouseCartesianPosition.y < point->y + MOVE_ZONE)
        {
            point->x = mouseCartesianPosition.x;
            point->y = mouseCartesianPosition.y;
        }
    }
}

void onMouseLeftClickDownTriangle()
{
    static const double MOVE_ZONE = 25.0;

    for (int i = 0; i < 3; ++i)
    {
        Vec2f *point = &trianglePoints[i];

        if ((double)GET_MOUSE_X() > point->x - MOVE_ZONE && (double)GET_MOUSE_X() < point->x + MOVE_ZONE &&
            (double)GET_MOUSE_Y() > point->y - MOVE_ZONE && (double)GET_MOUSE_Y() < point->y + MOVE_ZONE)
        {
            point->x = (double)GET_MOUSE_X();
            point->y = (double)GET_MOUSE_Y();
        }
    }
}

int gameLoop(void *arg)
{
    addMouseEventListener(MOUSE_MOVE, onMouseMotion);
    // addMouseEventListener(MOUSE_LEFT_BUTTON_PRESS, onMouseLeftClickDownParallelogram);
    addMouseEventListener(MOUSE_LEFT_BUTTON_PRESS, onMouseLeftClickDownTriangle);

    do
    {
        clearScreen();

        drawScreenCartesianPlane();

        // drawParallelogramWireCartesian2D(parallelogramPoints[0].x, parallelogramPoints[0].y, parallelogramPoints[1].x, parallelogramPoints[1].y, CYAN_500);
        // drawCircleFillCartesian2D(parallelogramPoints[0].x, parallelogramPoints[0].y, 10, RED);
        // drawCircleFillCartesian2D(parallelogramPoints[1].x, parallelogramPoints[1].y, 10, RED);

        // drawTriangleWire(
        //     trianglePoints[0].x, trianglePoints[0].y,
        //     trianglePoints[1].x, trianglePoints[1].y,
        //     trianglePoints[2].x, trianglePoints[2].y,
        //     CYAN_300);

        fast_drawTriangleFill(
            trianglePoints[0].x, trianglePoints[0].y,
            trianglePoints[1].x, trianglePoints[1].y,
            trianglePoints[2].x, trianglePoints[2].y,
            RED_800);
        
        fast_drawTriangleFill(
            640, 0,
            640,640,
            0,640,
            RED_800);
        
 
        for (int i = 0; i < 3; ++i)
        {
            drawFilledCircle(trianglePoints[i].x, trianglePoints[i].y, 10, RED);
        }

        draw_info();
        drawScreen();
        renderDelay(16); // Limit to 60 FPS
    } while (ON_GAME_RUNNING);

    return EXIT_SUCCESS;
}

CREATE_GAME(640, 640, "Basic Game Engine")