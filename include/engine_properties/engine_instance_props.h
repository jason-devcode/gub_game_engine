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

// Global screen dimensions
uint32_t gScreenWidth = 0;       // Width of the screen in pixels
uint32_t gScreenHeight = 0;      // Height of the screen in pixels
uint32_t gScreenTotalPixels = 0; // Total pixels in the screen

// Corrected pixel width for handling SDL screen pitch
uint32_t gCorrectPixelsWidth = 0; // Number of pixels per row in framebuffer

// Pointer to the framebuffer, where pixel data is stored
uint32_t *framebuffer = NULL;

// use for gameloop condition
bool ON_GAME_RUNNING = true;

#endif