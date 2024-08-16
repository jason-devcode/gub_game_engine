#include "../include/gub.h"

#include "../include/utils/geometry.h"
#include "../include/utils/cartesian_2D.h"

#include "../include/utils/font.h"

#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/pixel.h"
#include "../include/utils/vectorial_2D.h"

#include "../include/utils/mouse.h"
#include "../include/utils/keyboard.h"

#define draw_info()                            \
    drawFormattedText(                         \
        10, 10, 0xFFFFFF00,                    \
        "mouse screen position: ( %d, %d )\n", \
        GET_MOUSE_X(), GET_MOUSE_Y())

int bezierPointsCount = 3;

Vec2f *bezierPoints;

void onMouseLeftClickDownBezierPoints()
{
    static const double MOVE_ZONE = 25.0;

    for (int i = 0; i < bezierPointsCount; ++i)
    {
        Vec2f *point = &bezierPoints[i];

        if ((double)GET_MOUSE_X() > point->x - MOVE_ZONE && (double)GET_MOUSE_X() < point->x + MOVE_ZONE &&
            (double)GET_MOUSE_Y() > point->y - MOVE_ZONE && (double)GET_MOUSE_Y() < point->y + MOVE_ZONE)
        {
            point->x = (double)GET_MOUSE_X();
            point->y = (double)GET_MOUSE_Y();
        }
    }
}

// Function to initialize or reset Bezier points
void initializeBezierPoints()
{
    // Define the number of initial points
    static const int INITIAL_POINTS_COUNT = 3;

    // Allocate or reallocate memory for the Bezier points
    bezierPointsCount = INITIAL_POINTS_COUNT;
    bezierPoints = (Vec2f *)malloc(sizeof(Vec2f) * bezierPointsCount * 100);

    if (bezierPoints == NULL)
    {
        // Handle memory allocation failure
        return;
    }

    // Initialize the Bezier points with default values
    bezierPoints[0] = (Vec2f){100, 300};
    bezierPoints[1] = (Vec2f){300, 300};
    bezierPoints[2] = (Vec2f){500, 300};
    bezierPoints[3] = (Vec2f){550, 300};
    bezierPoints[4] = (Vec2f){550, 500};
    bezierPoints[5] = (Vec2f){450, 500};
}

bool pressOnce = false;

void onKeyNPress()
{
    if (pressOnce)
        return;
    bezierPointsCount -= 1;
    pressOnce = true;
}

void onKeyRelease()
{
    pressOnce = false;
}

void onKeyMPress()
{
    if (pressOnce || bezierPointsCount > 98)
        return;

    bezierPoints[bezierPointsCount].x = GET_MOUSE_X();
    bezierPoints[bezierPointsCount].y = GET_MOUSE_Y();
    bezierPointsCount += 1;
    pressOnce = true;
}

int gameLoop(void *argc)
{
    // setClearScreenColor(0xFFFF0000);
    initializeBezierPoints();
    initializeCartesian2DSpaceUtils(2, 2);

    addMouseEventListener(MOUSE_LEFT_BUTTON_PRESS, onMouseLeftClickDownBezierPoints);

    addKeyPressEventListener(GUB_KEY_n, onKeyNPress);
    addKeyPressEventListener(GUB_KEY_m, onKeyMPress);
    addKeyReleaseEventListener(GUB_KEY_n, onKeyRelease);
    addKeyReleaseEventListener(GUB_KEY_m, onKeyRelease);

    do
    {
        clearScreen();
        drawScreenCartesianPlane();
        drawBezierNPoints(bezierPoints, bezierPointsCount, 100, RGB(255, 255, 0));

        for (int i = 0; i < bezierPointsCount; ++i)
        {
            drawFilledCircle(bezierPoints[i].x, bezierPoints[i].y, 10, RED);
        }

        draw_info();
        drawScreen();
    } while (isGameRunning);

    free(bezierPoints);

    return EXIT_SUCCESS;
}

CREATE_GAME(600, 600, "BEZIER CURVE SAMPLE")