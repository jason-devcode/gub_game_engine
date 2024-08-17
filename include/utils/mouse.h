#ifndef MOUSE_UTILS_H
#define MOUSE_UTILS_H

#include "../core/managers/mouse_event_manager.h"
#include "../core/constants/mouse_event_values.h"

/**
 * @struct MouseState
 * @brief Structure to keep track of the mouse's state.
 *
 * This structure holds global data about the mouse, such as its position and button states.
 */
typedef struct
{
    int x; /**< The x-coordinate of the mouse cursor. */
    int y; /**< The y-coordinate of the mouse cursor. */
} MouseState;

// Global instance of MouseState
MouseState gMouseState = {0, 0};

/**
 * @brief Macro to get the X position of the mouse.
 *
 * @return The X position of the mouse.
 */
#define GET_MOUSE_X() (gMouseState.x)

/**
 * @brief Macro to get the Y position of the mouse.
 *
 * @return The Y position of the mouse.
 */
#define GET_MOUSE_Y() (gMouseState.y)

#endif // MOUSE_UTILS_H
