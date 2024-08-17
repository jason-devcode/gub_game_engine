#ifndef MOUSE_EVENT_MANAGER_H
#define MOUSE_EVENT_MANAGER_H

#include "event_manager.h"

// Global EventManager for mouse events
static EventManager gMouseEventManager;

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