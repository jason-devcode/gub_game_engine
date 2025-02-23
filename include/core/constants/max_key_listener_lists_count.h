#ifndef CONSTANT_MAX_KEY_LISTENER_LISTS_COUNT_H
#define CONSTANT_MAX_KEY_LISTENER_LISTS_COUNT_H

#ifdef USE_SDL_2
#include "SDL2/SDL_keycode.h"
#ifdef IN_ANDROID // In android SDL_SCANCODE_ENDCALL is not available
#define MAX_KEY_LISTENER_LISTS_COUNT 290
#else
#define MAX_KEY_LISTENER_LISTS_COUNT SDL_SCANCODE_ENDCALL
#endif
#define KeyCode SDL_KeyCode
#elif USE_SDL_1
#include "SDL/SDL_keysym.h"
#define MAX_KEY_LISTENER_LISTS_COUNT SDLK_LAST
#define KeyCode SDLKey
#else
#define MAX_KEY_LISTENER_LISTS_COUNT (0) // Default value for syntax highlighting
#endif

#endif