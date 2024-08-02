#ifndef KEY_PRESS_EVENT_MANAGER
#define KEY_PRESS_EVENT_MANAGER

#include "event_manager.h"

// global key event manager
EventManager gKeyPressEventManager = {NULL, 0};

#define addKeyPressEventListener(key, listener) \
    addEventListener(&gKeyPressEventManager, key, listener)

#define removeKeyPressEventListener(key, listener) \
    removeEventListener(&gKeyPressEventManager, key, listener)

#endif