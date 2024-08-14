#ifndef GRAPHIC_ENVIRONMENT_PROPERTIES_SDL1_H
#define GRAPHIC_ENVIRONMENT_PROPERTIES_SDL1_H

#include <SDL/SDL.h>

typedef struct _tag_graphic_environment_properties_
{

    SDL_Surface *screenSurface;
} GraphicEnvironment;

GraphicEnvironment gGameEngineGraphicEnvironment;

#endif