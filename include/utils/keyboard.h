#ifndef KEYBOARD_UTILS
#define KEYBOARD_UTILS

#include "../core/managers/key_press_event_manager.h"
#include "../core/managers/key_release_event_manager.h"

#ifndef USE_SDL_2
#include "SDL/SDL_keysym.h"
#define MAX_KEY_LISTENER_LISTS_COUNT SDLK_LAST
#define KeyCode SDLKey
#else
#include "SDL2/SDL_keycode.h"
#define MAX_KEY_LISTENER_LISTS_COUNT SDL_SCANCODE_ENDCALL
#define KeyCode SDL_KeyCode
#endif

#endif