#include "../include/gub.h"
#include "../include/utils/mouse.h"

void onMouseMotion()
{
    printf("Mouse coords: %d, %d\n", GET_MOUSE_X(), GET_MOUSE_Y());
}

void onClickLeftButton()
{
    puts("Click mouse left button");
}

void onClickRightButton()
{
    puts("Click mouse right button");
}

void onClickCenterButton()
{
    puts("Click mouse center button");
}

void onClickUpButton()
{
    puts("Click mouse wheel up button");
}

void onClickDownButton()
{
    puts("Click mouse wheel down button");
}

void onClickSlideTouchRight()
{
    puts("Click Slide touch right");
}

void onClickSlideTouchLeft()
{
    puts("Click Slide touch left");
}

void onReleaseLeftButton()
{
    puts("Release mouse left button");
}

void onReleaseRightButton()
{
    puts("Release mouse right button");
}

void onReleaseCenterButton()
{
    puts("Release mouse center button");
}

void onReleaseUpButton()
{
    puts("Release mouse wheel up button");
}

void onReleaseDownButton()
{
    puts("Release mouse wheel down button");
}

void onReleaseSlideTouchRight()
{
    puts("Release Slide touch right");
}

void onReleaseSlideTouchLeft()
{
    puts("Release Slide touch left");
}

int gameLoop(void *args)
{
    addMouseEventListener(MOUSE_MOVE, onMouseMotion);
    addMouseEventListener(MOUSE_LEFT_BUTTON_PRESS, onClickLeftButton);
    addMouseEventListener(MOUSE_RIGHT_BUTTON_PRESS, onClickRightButton);
    addMouseEventListener(MOUSE_MIDDLE_BUTTON_PRESS, onClickCenterButton);
    addMouseEventListener(MOUSE_WHEEL_UP_BUTTON_PRESS, onClickUpButton);
    addMouseEventListener(MOUSE_WHEEL_DOWN_BUTTON_PRESS, onClickDownButton);
    addMouseEventListener(TOUCH_LEFT_BUTTON_PRESS, onClickSlideTouchLeft);
    addMouseEventListener(TOUCH_RIGHT_BUTTON_PRESS, onClickSlideTouchRight); 

    addMouseEventListener(MOUSE_LEFT_BUTTON_RELEASE, onReleaseLeftButton);
    addMouseEventListener(MOUSE_RIGHT_BUTTON_RELEASE, onReleaseRightButton);
    addMouseEventListener(MOUSE_MIDDLE_BUTTON_RELEASE, onReleaseCenterButton);
    addMouseEventListener(MOUSE_WHEEL_UP_BUTTON_RELEASE, onReleaseUpButton);
    addMouseEventListener(MOUSE_WHEEL_DOWN_BUTTON_RELEASE, onReleaseDownButton);
    addMouseEventListener(TOUCH_LEFT_BUTTON_RELEASE, onReleaseSlideTouchLeft);
    addMouseEventListener(TOUCH_RIGHT_BUTTON_RELEASE, onReleaseSlideTouchRight);

    setClearScreenColor(0xFFFF0000);
    do
    {
        clearScreen();
        drawScreen();
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

CREATE_GAME(640, 480, "SAMPLE MOUSE EVENTS")
