#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <stdbool.h> // For boolean type and constants
#include <stdint.h>  // For fixed-width integer types
#include <SDL/SDL.h> // For SDL graphics functions
#include <pthread.h> // For POSIX thread functions

#include "utils/timers.h"   // For timers and time utils
#include "utils/keyboard.h" // For keyboard utils
#include "utils/mouse.h"    // For mouse utils
#include "utils/pixel.h"    // For pixel utils

#include "managers/event_processors.h" // For main event processors

#include "engine_properties/engine_instance_props.h" // For engine instance properties

/**
 * Initializes the SDL screen with the given width and height.
 *
 * @param screenWidth Width of the screen in pixels.
 * @param screenHeight Height of the screen in pixels.
 * @return Returns true if the screen is initialized successfully, false otherwise.
 */
bool initializeScreen(uint16_t screenWidth, uint16_t screenHeight)
{
    // Set the video mode with the given screen dimensions and 32-bit color depth
    gInstance.screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (gInstance.screen == NULL)
    {
        // Print an error message if screen initialization fails
        fprintf(stderr, "Cannot set video mode: %s\n", SDL_GetError());
        return false;
    }

    // Initialize global screen properties
    gScreenWidth = screenWidth;
    gScreenHeight = screenHeight;

    // Correct the pixel width calculation based on screen pitch
    gCorrectPixelsWidth = gInstance.screen->pitch >> 2; // >> 2 is equivalent to / 4

    gScreenTotalPixels = gCorrectPixelsWidth * screenHeight;

    // Set framebuffer pointer to the screen’s pixel data
    framebuffer = (uint32_t *)gInstance.screen->pixels;

    return true;
}

/**
 * Sets the window title for the SDL window.
 *
 * @param title The title to be displayed in the window’s title bar.
 */
void setWindowTitle(const char *title)
{
    SDL_WM_SetCaption(title, NULL); // Set the window title, with no icon text
}

/**
 * Initializes SDL and the graphics engine with the specified screen dimensions and window title.
 *
 * @param screenWidth Width of the screen in pixels.
 * @param screenHeight Height of the screen in pixels.
 * @param windowTitle The title of the SDL window.
 */
void initGraphicEngine(uint16_t screenWidth, uint16_t screenHeight, const char *windowTitle)
{
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Print an error message if SDL initialization fails
        fprintf(stderr, "Cannot initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialize Key Event Manager
    if (!initializeEventManager(&gKeyPressEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    {
        fputs("ERROR: Cannot initialize key press event manager", stderr);
        exit(EXIT_FAILURE);
    }

    if (!initializeEventManager(&gKeyReleaseEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    {
        fputs("ERROR: Cannot initialize key release event manager", stderr);
        exit(EXIT_FAILURE);
    }

    if (!initializeEventManager(&gMouseEventManager, MOUSE_LAST))
    {
        fputs("ERROR: Cannot initialize mouse event manager", stderr);
        exit(EXIT_FAILURE);
    }

    // Initialize the screen with the provided dimensions
    if (!initializeScreen(screenWidth, screenHeight))
        exit(EXIT_FAILURE);

    // Set the window title
    setWindowTitle(windowTitle);
}

/**
 * Initializes the game loop thread with the provided function.
 *
 * @param gameLoop Pointer to the function that will run in the game loop thread.
 * @return Returns true if the thread is created successfully, false otherwise.
 */
bool initializeGameLoop(void *(*gameLoop)(void *args))
{
    // Check if the game loop function is not null
    if (gameLoop == NULL)
        return false;

    // Create the game loop thread
    if (pthread_create(&gInstance.gameThread, NULL, gameLoop, NULL) != 0)
    {
        // Print an error message if thread creation fails
        fprintf(stderr, "Cannot create game loop process\n");
        exit(EXIT_FAILURE);
    }

    return true;
}

static bool keysPressed[MAX_KEY_LISTENER_LISTS_COUNT] = {false};
static bool mouseButtonsPressed[MOUSE_LAST + 1] = {false}; // For left, middle, right, wheel up, wheel down

// Main function
void processAllEvents()
{
    SDL_Event event;

    // Process all pending events
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            PROCESS_KEYDOWN(event);
            break;
        case SDL_KEYUP:
            PROCESS_KEYUP(event);
            break;
        case SDL_MOUSEMOTION:
            PROCESS_MOUSEMOTION(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            PROCESS_MOUSEBUTTONDOWN(event);
            break;
        case SDL_MOUSEBUTTONUP:
            PROCESS_MOUSEBUTTONUP(event);
            break;
        case SDL_QUIT:
            PROCESS_QUIT(event);
            break;
        }
    }

    // Trigger events for all keys still pressed
    TRIGGER_PRESSED_KEYS();

    // Trigger events for all mouse buttons still pressed
    TRIGGER_PRESSED_MOUSE_BUTTONS();
}

/**
 * Runs the main engine loop, handling events and maintaining the engine state.
 */
void runEngine()
{
    ON_GAME_RUNNING = true;

    // Main loop of the engine
    if (ON_GAME_RUNNING)
    {
        do
        {
            processAllEvents(); // Handle events
        } while (ON_GAME_RUNNING);
    }
}

/**
 * Cancels and joins the game loop thread to clean up resources.
 */
void clearGameLoopThread()
{
    ON_GAME_RUNNING = false;
    pthread_join(gInstance.gameThread, NULL);
}

/**
 * clear keyboard event managers resources
 */
void clearKeyboardManagers()
{
    freeEventManager(&gMouseEventManager, true);
    freeEventManager(&gKeyPressEventManager, true);
    freeEventManager(&gKeyReleaseEventManager, true);
}

/**
 * Cleans up and shuts down the graphics engine.
 */
void clearEngine()
{
    clearKeyboardManagers();
    clearGameLoopThread(); // Clean up the game loop thread
    SDL_Quit();            // Shut down SDL
    exit(EXIT_SUCCESS);
}



// Macro to update the screen with the current framebuffer contents
#define drawScreen()            \
    SDL_Flip(gInstance.screen); \
    UPDATE_TIMERS()

// Macro to fill the screen with black color
#define clearScreen()                                                                                               \
    register uint64_t *endPixels = (uint64_t *)(&framebuffer[gScreenTotalPixels - 1]);                              \
    for (register uint64_t *pixelsIterator = (uint64_t *)framebuffer; pixelsIterator < endPixels; ++pixelsIterator) \
        *pixelsIterator = 0x0000000000000000LL;

#endif