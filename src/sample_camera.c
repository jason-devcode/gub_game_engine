#include "../include/gub.h"
#include "../include/utils/keyboard.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/geometry.h"
#include "../include/utils/analytic_geometry.h"
#include "../include/utils/gamma.h"
#include "../include/utils/vectorial_2D.h"
#include "../include/utils/cartesian_2D.h"

#include "../include/utils/3DEngine/camera3D.h"

#define draw_info()                                                                                                                                             \
    drawFormattedText(                                                                                                                                          \
        10, 10, 0xFFFFFF00,                                                                                                                                     \
        "FPS: %d\ndeltatime: %lf\nmouse screen position: ( %d, %d )\n\ncamera direction: ( %0.2lf, %0.2lf, %0.2lf)\ncamera angle: ( %0.2lf, %0.2lf, %0.2lf)\n", \
        getFps(), getDeltatime(),                                                                                                                               \
        GET_MOUSE_X(), GET_MOUSE_Y(), cameraDirection.x, cameraDirection.y, cameraDirection.z, cameraPitch, cameraYaw, cameraRoll)

void onPressKey_Up_W()
{
    cameraPitch += radian * getDeltatime() * 0.001;
    updateCameraDirection();
}

void onPressKey_Down_S()
{
    cameraPitch -= radian * getDeltatime() * 0.001;
    updateCameraDirection();
}

void onPressKey_Left_A()
{
    cameraYaw -= radian * getDeltatime() * 0.001;
    updateCameraDirection();
}

void onPressKey_Right_D()
{
    cameraYaw += radian * getDeltatime() * 0.001;
    updateCameraDirection();
}

int gameLoop(void *arg)
{
    initializeCamera3D((Vec3f){.x = 0, .y = 0, .z = -2}, (Vec3f){.x = 0, .y = 0, .z = 0}, degreesToRadians(60));

    addKeyPressEventListener(GUB_KEY_w, onPressKey_Up_W);
    addKeyPressEventListener(GUB_KEY_UP, onPressKey_Up_W);
    addKeyPressEventListener(GUB_KEY_s, onPressKey_Down_S);
    addKeyPressEventListener(GUB_KEY_DOWN, onPressKey_Down_S);
    addKeyPressEventListener(GUB_KEY_a, onPressKey_Left_A);
    addKeyPressEventListener(GUB_KEY_LEFT, onPressKey_Left_A);
    addKeyPressEventListener(GUB_KEY_d, onPressKey_Right_D);
    addKeyPressEventListener(GUB_KEY_RIGHT, onPressKey_Right_D);

    do
    {
        clearScreen();

        drawScreenCartesianPlane();

        draw_info();
        drawScreen();
        renderDelay(16); // Limit to 60 FPS
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

CREATE_GAME(640, 640, "Basic Game Engine")