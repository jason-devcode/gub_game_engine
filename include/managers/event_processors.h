#ifndef EVENT_PROCESSORS_H
#define EVENT_PROCESSORS_H

/**
 * Macro to handle SDL_KEYDOWN events.
 * This macro checks if the key is already pressed. If not, it updates the
 * state to pressed and triggers a key press event.
 *
 * @param event The SDL event to process.
 */
#define PROCESS_KEYDOWN(event)                        \
    {                                                 \
        int key = (event).key.keysym.sym;             \
        if (!keysPressed[key])                        \
        {                                             \
            keysPressed[key] = true;                  \
            triggerEvent(gKeyPressEventManager, key); \
        }                                             \
    }

/**
 * Macro to handle SDL_KEYUP events.
 * This macro checks if the key is pressed. If so, it updates the state to
 * not pressed and triggers a key release event.
 *
 * @param event The SDL event to process.
 */
#define PROCESS_KEYUP(event)                            \
    {                                                   \
        int key = (event).key.keysym.sym;               \
        if (keysPressed[key])                           \
        {                                               \
            keysPressed[key] = false;                   \
            triggerEvent(gKeyReleaseEventManager, key); \
        }                                               \
    }

/**
 * Macro to handle SDL_MOUSEMOTION events.
 * This macro updates the mouse state with the new mouse position and triggers
 * a mouse move event.
 *
 * @param event The SDL event to process.
 */
#define PROCESS_MOUSEMOTION(event)                    \
    {                                                 \
        gMouseState.x = (event).motion.x;             \
        gMouseState.y = (event).motion.y;             \
        triggerEvent(gMouseEventManager, MOUSE_MOVE); \
    }

/**
 * Macro to handle SDL_MOUSEBUTTONDOWN events.
 * This macro checks if the mouse button is already pressed. If not, it updates
 * the state to pressed and triggers a mouse button press event.
 *
 * @param event The SDL event to process.
 */
#define PROCESS_MOUSEBUTTONDOWN(event)                \
    {                                                 \
        int button = (event).button.button;           \
        if (!mouseButtonsPressed[button - 1])         \
        {                                             \
            mouseButtonsPressed[button - 1] = true;   \
            triggerEvent(gMouseEventManager, button); \
        }                                             \
    }

/**
 * Macro to handle SDL_MOUSEBUTTONUP events.
 * This macro checks if the mouse button is pressed. If so, it updates the state
 * to not pressed and triggers a mouse button release event.
 *
 * @param event The SDL event to process.
 */
#define PROCESS_MOUSEBUTTONUP(event)                      \
    {                                                     \
        int button = (event).button.button;               \
        if (mouseButtonsPressed[button - 1])              \
        {                                                 \
            mouseButtonsPressed[button - 1] = false;      \
            triggerEvent(gMouseEventManager, button + 5); \
        }                                                 \
    }

/**
 * Macro to handle SDL_QUIT events.
 * This macro sets the global variable `ON_GAME_RUNNING` to false, indicating
 * that the game should exit.
 *
 * @param event The SDL event to process.
 */
#define PROCESS_QUIT(event)      \
    {                            \
        ON_GAME_RUNNING = false; \
    }

/**
 * Macro to trigger events for all keys still pressed.
 * This macro iterates over all possible key states and triggers a key press event
 * for each key that remains pressed.
 */
#define TRIGGER_PRESSED_KEYS()                                          \
    {                                                                   \
        for (register int i = 0; i < MAX_KEY_LISTENER_LISTS_COUNT; ++i) \
        {                                                               \
            if (keysPressed[i])                                         \
            {                                                           \
                triggerEvent(gKeyPressEventManager, i);                 \
            }                                                           \
        }                                                               \
    }

/**
 * Macro to trigger events for all mouse buttons still pressed.
 * This macro iterates over all possible mouse button states and triggers a
 * mouse button event for each button that remains pressed.
 */
#define TRIGGER_PRESSED_MOUSE_BUTTONS()              \
    {                                                \
        for (int i = 1; i < MOUSE_LAST + 1; ++i)     \
        {                                            \
            if (mouseButtonsPressed[i - 1])          \
            {                                        \
                triggerEvent(gMouseEventManager, i); \
            }                                        \
        }                                            \
    }

#endif