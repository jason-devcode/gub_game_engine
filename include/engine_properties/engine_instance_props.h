#ifndef ENGINE_INSTANCE_PROPS
#define ENGINE_INSTANCE_PROPS

#include <stdint.h>
#include <pthread.h>
#include <SDL/SDL.h>

#include "../managers/event_manager.h"

// TODO: Use global properties for avoid innecesary memory address calculations and for simplicity

// Define a structure to hold the state of the graphics engine
typedef struct
{
    SDL_Surface *screen;           // Pointer to the SDL surface representing the screen
    pthread_t gameThread;          // Thread identifier for the game loop
    void *(*gameLoop)(void *args); // Function pointer to the game loop function
} EngineInstance;

// TODO: The global prefix 'g' denotes global variables for simplicity and performance

EngineInstance gInstance; // Global instance of the EngineInstance structure

#include "screen_dimensions.h"
#include "framebuffer.h"
#include "running_state.h"

#endif