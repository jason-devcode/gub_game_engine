#ifndef GRAPHIC_ENVIRONMENT_PROPERTIES_SDL2_H
#define GRAPHIC_ENVIRONMENT_PROPERTIES_SDL2_H

#include <SDL2/SDL.h>

typedef struct _tag_graphic_environment_properties_
{

    SDL_Window *window;
    SDL_Surface *screenSurface;
} GraphicEnvironment;

static GraphicEnvironment gGameEngineGraphicEnvironment;

#endif