#ifndef KEY_EVENT_MANAGER
#define KEY_EVENT_MANAGER

#ifndef USE_SDL_2
#include "SDL/SDL_keysym.h"
#define MAX_KEY_LISTENER_LISTS_COUNT SDLK_LAST
#define KeyCode SDLKey
#else
#include "SDL2/SDL_keycode.h"
#define MAX_KEY_LISTENER_LISTS_COUNT SDLK_ENDCALL
#define KeyCode SDL_KeyCode
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct KeyListener
{
    void (*onKeyEvent)();
    struct KeyListener *next;
} KeyListener;

typedef struct KeyEventManager
{
    KeyListener *keyListenersList[MAX_KEY_LISTENER_LISTS_COUNT];
} KeyEventManager;
#define SIZEOF_KEYEVENTMANAGER sizeof(KeyEventManager)

#define keyEventListenersforEach(listenersList, action) \
    KeyListener **current = listenersList;              \
    while (*current)                                    \
    {                                                   \
        action                                          \
            current = &(*current)->next;                \
    }

bool KeyEventManager_init(KeyEventManager *manager)
{
    if (manager == NULL)
        return true;

    for (int listenerListIterator = 0; listenerListIterator < MAX_KEY_LISTENER_LISTS_COUNT; ++listenerListIterator)
        manager->keyListenersList[listenerListIterator] = NULL;

    return false;
}

void KeyEventManager_addKeyEventListener(KeyEventManager *manager, KeyCode key, void (*onKeyEvent)(void))
{
    if (onKeyEvent == NULL)
        return;
    KeyListener *listener = (KeyListener *)malloc(sizeof(KeyListener));
    listener->onKeyEvent = onKeyEvent;
    listener->next = manager->keyListenersList[key];
    manager->keyListenersList[key] = listener;
}

void KeyEventManager_removeKeyEventListener(KeyEventManager *manager, KeyCode key, void (*onKeyEvent)(void)){
    keyEventListenersforEach(&manager -> keyListenersList[key], {
        if ((*current)->onKeyEvent == onKeyEvent)
        {
            KeyListener *toRemove = *current;
            *current = (*current)->next;
            free(toRemove);
            return;
        }
    })}

#define KeyEventManager_handleEvent(manager, key)          \
    KeyListener *listener = manager.keyListenersList[key]; \
    while (listener)                                       \
    {                                                      \
        listener->onKeyEvent();                            \
        listener = listener->next;                         \
    }

#endif