#include "../include/game_engine.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/raster.h"
#include "../include/utils/geometry.h"
#include "../include/utils/gamma.h"
#include "../include/utils/vectorial_2D.h"
#include "../include/utils/cartesian_2D.h"

Vec2f mouseCartesianPosition = {0, 0};
Vec2f parallelogramPoints[2] = {
    {.x = 4, .y = 0},
    {.x = 4, .y = 4}};

#define calculateAreaParallelogram(x1, y1, x2, y2) \
    ((x1 * y2) - (x2 * y1))

#define draw_info()                                                                                                                             \
    drawFormattedText(                                                                                                                          \
        10, 10, 0xFFFFFF00,                                                                                                                     \
        "FPS: %d\ndeltatime: %lf\nmouse screen position: ( %d, %d )\nmouse cartesian position: ( %0.2lf, %0.2lf )\narea parallelogram: %0.2lf", \
        getFps(), getDeltatime(),                                                                                                               \
        GET_MOUSE_X(), GET_MOUSE_Y(),                                                                                                           \
        mouseCartesianPosition.x, mouseCartesianPosition.y,                                                                                     \
        calculateAreaParallelogram(                                                                                                             \
            parallelogramPoints[0].x, parallelogramPoints[0].y, parallelogramPoints[1].x, parallelogramPoints[1].y))

void onMouseMotion()
{
    mouseCartesianPosition.x = convertScreenXToCartesian2DX(GET_MOUSE_X());
    mouseCartesianPosition.y = convertScreenYToCartesian2DY(GET_MOUSE_Y());
}

void onMouseLeftClickDown()
{
#define MOVE_ZONE 0.5
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

void *gameLoop(void *arg)
{
    addMouseEventListener(MOUSE_MOVE, onMouseMotion);
    addMouseEventListener(MOUSE_LEFT_BUTTON_DOWN, onMouseLeftClickDown);
    do
    {
        clearScreen();

        drawScreenCartesianPlane();

        drawParallelogramWireCartesian2D(parallelogramPoints[0].x, parallelogramPoints[0].y, parallelogramPoints[1].x, parallelogramPoints[1].y, CYAN_500);

        drawCircleFillCartesian2D(parallelogramPoints[0].x, parallelogramPoints[0].y, 10, RED);
        drawCircleFillCartesian2D(parallelogramPoints[1].x, parallelogramPoints[1].y, 10, RED);

        draw_info();
        drawScreen();
        renderDelay(16); // Limit to 60 FPS
    } while (ON_GAME_RUNNING);

    return NULL;
}

CREATE_GAME(640, 640, "Basic Game Engine");