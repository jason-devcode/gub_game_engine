#ifndef KEY_RELEASE_EVENT_MANAGER
#define KEY_RELEASE_EVENT_MANAGER

#include "event_manager.h"

EventManager gKeyReleaseEventManager = {NULL, 0};

// Release key
#define addKeyReleaseEventListener(key, listener) \
    addEventListener(&gKeyReleaseEventManager, key, listener)

#define removeKeyReleaseEventListener(key, listener) \
    removeEventListener(&gKeyReleaseEventManager, key, listener)

#endif