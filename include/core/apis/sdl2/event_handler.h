#ifndef EVENT_API_HANDLER_SDL_2_IMPLEMENTATION_H
#define EVENT_API_HANDLER_SDL_2_IMPLEMENTATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "graphic_environment.h"

#include "../../engine_properties/running_state.h"
#include "../../engine_properties/pause_gameloop_for_rendering.h"

#include "../../../utils/keyboard.h" // For keyboard utils
#include "../../../utils/joystick.h" // For joystick utils
#include "../../../utils/mouse.h"    // For mouse utils

#include "../../managers/event_processors.h" // For main event processors

#include "../../constants/joystick_init_possible_results.h"
#include "joystick_event_handler.h"

/**
 * @brief Sets the render delay value.
 *
 * This macro utilizes SDL_Delay to pause execution for the given delay value.
 *
 * @param delayValue The value for the render delay.
 */
#define renderDelay(delayValue) SDL_Delay(delayValue)

/**
 * @brief Initializes the event managers.
 *
 * This function sets up the event managers for key presses, key releases, and mouse events.
 * It allocates necessary resources and handles initialization errors.
 *
 * @return true if all event managers are successfully initialized; false otherwise.
 */
bool initializeEventManagers()
{
    // Initialize Key Event Manager
    if (!initializeEventManager(&gKeyPressEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    {
        fputs("ERROR: Could not initialize key press event manager", stderr);
        goto fail_initialization;
    }

    if (!initializeEventManager(&gKeyReleaseEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    {
        fputs("ERROR: Could not initialize key release event manager", stderr);
        goto fail_initialization;
    }

    if (!initializeEventManager(&gMouseEventManager, MOUSE_LAST))
    {
        fputs("ERROR: Could not initialize mouse event manager", stderr);
        goto fail_initialization;
    }

    const int initJoystickResult = initializeJoystickEventHandler();

    if (initJoystickResult != NOT_FOUND_JOYSTICK && !initJoystickResult)
    {
        fputs("ERROR: Could not initialize joystick events handler\n", stderr);
        goto fail_initialization;
    }

    goto success_initalization;

fail_initialization:
    freeEventManager(&gKeyPressEventManager, true);
    freeEventManager(&gKeyReleaseEventManager, true);
    freeEventManager(&gMouseEventManager, true);
    closeJoystickEventHandler();
    return false;

success_initalization:
    return true;
}

/**
 * @brief Pushes a wheel event onto the event queue.
 *
 * This function creates and pushes a wheel event of the specified type and direction.
 *
 * @param type The type of the event to push (e.g., SDL_MOUSEBUTTONDOWN).
 * @param direction The direction of the wheel event (e.g., MOUSE_WHEEL_UP_BUTTON_PRESS).
 */
void push_wheel_event(Uint32 type, int direction)
{
    SDL_Event event;
    event.type = type;
    event.button.button = direction;
    SDL_PushEvent(&event);
}

/**
 * @brief Main event handling loop.
 *
 * This function continuously processes all events while the game is running.
 * It handles various types of SDL events, including key presses, mouse movements,
 * mouse wheel events, and more. It also handles updating the window surface if needed
 * and triggers events for keys, mouse buttons, and other input devices.
 */
void loopEventHandlerApi()
{
    SDL_Event event;
    do
    {
        /**
         * @brief Updates the window surface if rendering is pending and resumes the game loop.
         *
         * In SDL 2, window surface updates must be performed on the main thread. This code ensures that
         * rendering updates are properly applied even if the game loop is running on a different thread.
         *
         * If `pauseGameLoopForRendering` is true, indicating that the game loop should be paused to allow
         * rendering to complete:
         * - The window surface is updated using `SDL_UpdateWindowSurface()` to ensure that changes are visible.
         * - The game loop is resumed with `resumeGameloop()` to continue processing after the rendering update.
         *
         * This mechanism addresses the limitation in SDL 2 where only the main thread can make window surface updates.
         */
        if (pauseGameLoopForRendering)
        {
            SDL_UpdateWindowSurface(gGameEngineGraphicEnvironment.window);
            resumeGameloop();
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
            {
                PROCESS_KEYDOWN(event);
                break;
            }
            case SDL_KEYUP:
            {
                PROCESS_KEYUP(event);
                break;
            }
            case SDL_MOUSEMOTION:
            {
                PROCESS_MOUSEMOTION(event);
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                if (event.wheel.y > 0)
                {
                    push_wheel_event(SDL_MOUSEBUTTONDOWN, MOUSE_WHEEL_UP_BUTTON_PRESS);
                    push_wheel_event(SDL_MOUSEBUTTONUP, MOUSE_WHEEL_UP_BUTTON_PRESS);
                }
                else if (event.wheel.y < 0)
                {
                    push_wheel_event(SDL_MOUSEBUTTONDOWN, MOUSE_WHEEL_DOWN_BUTTON_PRESS);
                    push_wheel_event(SDL_MOUSEBUTTONUP, MOUSE_WHEEL_DOWN_BUTTON_PRESS);
                }
                if (event.wheel.x < 0)
                {
                    push_wheel_event(SDL_MOUSEBUTTONDOWN, TOUCH_LEFT_BUTTON_PRESS);
                    push_wheel_event(SDL_MOUSEBUTTONUP, TOUCH_LEFT_BUTTON_PRESS);
                }
                else if (event.wheel.x > 0)
                {
                    push_wheel_event(SDL_MOUSEBUTTONDOWN, TOUCH_RIGHT_BUTTON_PRESS);
                    push_wheel_event(SDL_MOUSEBUTTONUP, TOUCH_RIGHT_BUTTON_PRESS);
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                PROCESS_MOUSEBUTTONDOWN(event);
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                PROCESS_MOUSEBUTTONUP(event);
                break;
            }
            case SDL_QUIT:
            {
                PROCESS_QUIT(event);
                break;
            }
            default:
                handleJoystickEvents(&event);
                break;
            }
        }

        // Trigger events for all joystick buttons still pressed
        TRIGGER_PRESSED_JOYSTICKS_BUTTONS();

        // Trigger events for all keys still pressed
        TRIGGER_PRESSED_KEYS();

        // Trigger events for all mouse buttons still pressed
        TRIGGER_PRESSED_MOUSE_BUTTONS();
    } while (isGameRunning);
}

/**
 * @brief Cleans up and shuts down the event managers.
 *
 * This function releases resources used by the event managers and performs
 * any necessary cleanup.
 */
void closeEventManagers()
{
    freeEventManager(&gMouseEventManager, true);
    freeEventManager(&gKeyPressEventManager, true);
    freeEventManager(&gKeyReleaseEventManager, true);
    closeJoystickEventHandler();
}

#endif