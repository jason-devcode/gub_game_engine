#ifndef ENGINE_INSTANCE_PROP_H
#define ENGINE_INSTANCE_PROP_H

#include <pthread.h>       // For pthread_t
#include <SDL/SDL_video.h> // For SDL_Surface

// Define a structure to hold the state of the graphics engine
typedef struct
{
    SDL_Surface *screen;           // Pointer to the SDL surface representing the screen
    pthread_t gameThread;          // Thread identifier for the game loop
    void *(*gameLoop)(void *args); // Function pointer to the game loop function
} EngineInstance;

EngineInstance gInstance; // Global instance of the EngineInstance structure

#endif