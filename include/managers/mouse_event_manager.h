#ifndef MOUSE_EVENT_MANAGER_H
#define MOUSE_EVENT_MANAGER_H

#include "event_manager.h"

/**
 * @enum MouseEventType
 * @brief Enumeration of possible mouse event types.
 *
 * This enumeration defines the different types of mouse events that can be handled
 * by the EventManager.
 */
typedef enum
{
    MOUSE_MOVE,               /**< Event for mouse movement. */
    MOUSE_LEFT_BUTTON_DOWN,   /**< Event for mouse left button press. */
    MOUSE_MIDDLE_BUTTON_DOWN, /**< Event for mouse middle button press. */
    MOUSE_RIGHT_BUTTON_DOWN,  /**< Event for mouse right button press. */
    MOUSE_WHELL_BUTTON_UP,    /**< Event for mouse wheel up. */
    MOUSE_WHELL_BUTTON_DOWN,  /**< Event for mouse wheel down. */
    MOUSE_LEFT_BUTTON_UP,     /**< Event for mouse left button release. */
    MOUSE_MIDDLE_BUTTON_UP,   /**< Event for mouse middle button release. */
    MOUSE_RIGHT_BUTTON_UP,    /**< Event for mouse right button release. */
    MOUSE_LAST
} MouseEventType;

// Global EventManager for mouse events
EventManager gMouseEventManager;

/**
 * @brief Adds a mouse event listener.
 *
 * This macro registers a listener for a specific type of mouse event.
 *
 * @param type The type of mouse event to listen for.
 * @param listener The function to call when the event is triggered.
 * @return true if the listener was successfully added, false otherwise.
 */
#define addMouseEventListener(type, listener) \
    addEventListener(&gMouseEventManager, (uint32_t)(type), (listener))

/**
 * @brief Removes a mouse event listener.
 *
 * This macro removes a listener for a specific type of mouse event.
 *
 * @param type The type of mouse event to stop listening for.
 * @param listener The function to remove.
 * @return true if the listener was successfully removed, false otherwise.
 */
#define removeMouseEventListener(type, listener) \
    removeEventListener(&gMouseEventManager, (uint32_t)(type), (listener))

#endif