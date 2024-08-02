#include "../include/game_engine.h"
#include "../include/utils/geometry.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"

#include "../include/managers/event_manager.h"

typedef struct Vec2f
{
    double x, y;
} Vec2f;

Vec2f playerPosition = {0, 0};

void onPlayerMoveForward()
{
    playerPosition.y += getDeltatime() * 0.001;
}

void onPlayerMoveBackward()
{
    playerPosition.y -= getDeltatime() * 0.001;
}

void onPlayerRotateRight()
{
    playerPosition.x += getDeltatime() * 0.001;
}

void onPlayerRotateLeft()
{
    playerPosition.x -= getDeltatime() * 0.001;
}

void onLeftUpClick()
{
    puts("Solto izquierda");
}

void onRightUpClick()
{
    puts("Solto derecha");
}

void onCursorMotion()
{
    puts("Moviendo mouse");
}

void *gameLoop(void *arg)
{
    addKeyPressEventListener(SDLK_w, onPlayerMoveForward);
    addKeyPressEventListener(SDLK_s, onPlayerMoveBackward);
    addKeyPressEventListener(SDLK_a, onPlayerRotateLeft);
    addKeyPressEventListener(SDLK_d, onPlayerRotateRight);

    addMouseEventListener(MOUSE_MOVE, onCursorMotion);
    addMouseEventListener(MOUSE_LEFT_BUTTON_DOWN, onPlayerRotateLeft);
    addMouseEventListener(MOUSE_RIGHT_BUTTON_DOWN, onPlayerRotateRight);
    addMouseEventListener(MOUSE_LEFT_BUTTON_UP, onLeftUpClick);
    addMouseEventListener(MOUSE_RIGHT_BUTTON_UP, onRightUpClick);

    do
    {
        clearScreen();

        drawFormattedText(
            10, 10, 0xFFFFFF00,
            "FPS: %d\ndeltatime: %lf\nplayer coords: (%lf, %lf,) \n",
            getFps(), getDeltatime(),
            playerPosition.x, playerPosition.y);

        drawScreen();

        renderDelay(16); // Limit to 60  FPS
    } while (ON_GAME_RUNNING);

    return NULL;
}

CREATE_GAME(640, 480, "Basic Game Engine");