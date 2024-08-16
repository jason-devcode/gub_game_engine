#ifndef EVENT_API_HANDLER_SDL_2_IMPLEMENTATION_H
#define EVENT_API_HANDLER_SDL_2_IMPLEMENTATION_H

#include <SDL/SDL.h>
#include <stdbool.h>

#include "graphic_environment.h"

#include "../../engine_properties/running_state.h"
#include "../../engine_properties/pause_gameloop_for_rendering.h"

#include "../../../utils/keyboard.h" // For keyboard utils
#include "../../../utils/joystick.h" // For joystick utils
#include "../../../utils/mouse.h"    // For mouse utils

#include "../../managers/event_processors.h" // For main event processors

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
        fputs("ERROR: Cannot initialize key press event manager", stderr);
        goto fail_initialization;
    }

    if (!initializeEventManager(&gKeyReleaseEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    {
        fputs("ERROR: Cannot initialize key release event manager", stderr);
        goto fail_initialization;
    }

    if (!initializeEventManager(&gMouseEventManager, MOUSE_LAST))
    {
        fputs("ERROR: Cannot initialize mouse event manager", stderr);
        goto fail_initialization;
    }

    goto success_initalization;

fail_initialization:
    freeEventManager(&gKeyPressEventManager, true);
    freeEventManager(&gKeyReleaseEventManager, true);
    freeEventManager(&gMouseEventManager, true);
    return false;

success_initalization:
    return true;
}

/**
 * @brief Processes all pending events.
 *
 * This function polls and processes all SDL events, including key presses,
 * key releases, mouse movements, and button clicks. It also triggers events
 * for any joystick buttons, keys, and mouse buttons that are still pressed.
 */
void processAllEvents()
{
    SDL_Event event;

    // Process all pending events
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
            // default:
            //     handleJoystickEvents(&event);
            //     break;
        }
    }
    // Trigger events for all joystick buttons still pressed
    // TRIGGER_PRESSED_JOYSTICKS_BUTTONS();

    // Trigger events for all keys still pressed
    TRIGGER_PRESSED_KEYS();

    // Trigger events for all mouse buttons still pressed
    TRIGGER_PRESSED_MOUSE_BUTTONS();
}

/**
 * @brief Main event handler loop.
 *
 * This function continuously processes all events while the game is running.
 * It repeatedly calls `processAllEvents` until the game is no longer running.
 */
void loopEventHandlerApi()
{
    do
    {
        processAllEvents();
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

    // closeJoystickManager();
    // if (gJoyStickEventManager.listsCount > 0)
    // freeEventManager(&gJoyStickEventManager, true);
}

#endif