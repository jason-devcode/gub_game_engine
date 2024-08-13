#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/geometry.h"
#include "../include/utils/pixel.h"
#include "../include/utils/font.h"
#include "../include/utils/joystick.h"
#include "../include/game_engine.h"

void pressButtonAJoystick()
{
    puts("BUTTON A PRESSED");
}

void releaseButtonAJoystick()
{
    puts("BUTTON A RELEASE");
}

void pressButtonBJoystick()
{
    puts("BUTTON B PRESSED");
}

void releaseButtonBJoystick()
{
    puts("BUTTON B RELEASE");
}

void pressButtonXJoystick()
{
    puts("BUTTON X PRESSED");
}

void releaseButtonXJoystick()
{
    puts("BUTTON X RELEASE");
}

void pressButtonYJoystick()
{
    puts("BUTTON Y PRESSED");
}

void releaseButtonYJoystick()
{
    puts("BUTTON Y RELEASE");
}

int gameLoop(void *ignore)
{
    initializeJoystickManager();

    addJoystickEventListener(JOY_BUTTON_0_PRESS, JOYSTICK_PLAYER_1, pressButtonAJoystick);
    addJoystickEventListener(JOY_BUTTON_0_RELEASE, JOYSTICK_PLAYER_1, releaseButtonAJoystick);

    addJoystickEventListener(JOY_BUTTON_1_PRESS, JOYSTICK_PLAYER_1, pressButtonBJoystick);
    addJoystickEventListener(JOY_BUTTON_1_RELEASE, JOYSTICK_PLAYER_1, releaseButtonBJoystick);

    addJoystickEventListener(JOY_BUTTON_2_PRESS, JOYSTICK_PLAYER_1, pressButtonXJoystick);
    addJoystickEventListener(JOY_BUTTON_2_RELEASE, JOYSTICK_PLAYER_1, releaseButtonXJoystick);

    addJoystickEventListener(JOY_BUTTON_3_PRESS, JOYSTICK_PLAYER_1, pressButtonYJoystick);
    addJoystickEventListener(JOY_BUTTON_3_RELEASE, JOYSTICK_PLAYER_1, releaseButtonYJoystick);

    JoystickState *joystickPlayer1 = getJoystickState(JOYSTICK_PLAYER_1);

    double X1 = 128, X2 = 256, X3 = 384;
    double Y1 = 128, Y2 = 256, Y3 = 384;

    do
    {
        clearScreenDepth();

        drawFilledCircle(X1, Y1, 10, RED_700);
        drawFilledCircle(X2, Y2, 10, GREEN_700);
        drawFilledCircle(X3, Y3, 10, BLUE_700);

        X1 += joystickPlayer1->motionHatX * 4;
        Y1 += joystickPlayer1->motionHatY * 4;

        X2 += joystickPlayer1->motionLeftAxisX * 4;
        Y2 += joystickPlayer1->motionLeftAxisY * 4;

        X3 += joystickPlayer1->motionRightAxisX * 4;
        Y3 += joystickPlayer1->motionRightAxisY * 4;

        drawFormattedText(10, 10, YELLOW, "left lever motion -  X: %lf Y: %lf\nright lever motion -  X: %lf Y: %lf\n", joystickPlayer1->motionLeftAxisX, joystickPlayer1->motionLeftAxisY, joystickPlayer1->motionRightAxisX, joystickPlayer1->motionRightAxisY);

        drawScreen();
        renderDelay(16);
    } while (ON_GAME_RUNNING);

    return EXIT_SUCCESS;
}

CREATE_GAME(512, 512, "JOYSTICK EVENT MANAGER SAMPLE")