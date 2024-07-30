#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <stdbool.h> // For boolean type and constants
#include <stdint.h>  // For fixed-width integer types
#include <SDL/SDL.h> // For SDL graphics functions
#include <pthread.h> // For POSIX thread functions

#pragma region GRAPHIC_ENGINE_INSTANCE_PROPERTIES

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
uint32_t gScreenWidth = 0;  // Width of the screen in pixels
uint32_t gScreenHeight = 0; // Height of the screen in pixels

// Corrected pixel width for handling SDL screen pitch
uint32_t gCorrectPixelsWidth = 0; // Number of pixels per row in framebuffer

// Pointer to the framebuffer, where pixel data is stored
uint32_t *framebuffer = NULL;

#pragma endregion GRAPHIC_ENGINE_INSTANCE_PROPERTIES

// use for gameloop condition
#define ON_GAME_RUNNING true


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

/**
 * Handles SDL events such as window close requests.
 *
 * @param running Pointer to a boolean indicating whether the engine should keep running.
 */
void handleEvents(bool *running)
{
    SDL_Event event;
    // Process all pending events
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            // Set running to false if a quit event is detected
            *running = false;
        }
    }
}

/**
 * Runs the main engine loop, handling events and maintaining the engine state.
 */
void runEngine()
{
    bool running = true;

    // Main loop of the engine
    while (running)
    {
        handleEvents(&running); // Handle events
        SDL_Delay(16);          // Delay to achieve approximately 60 FPS
    }
}

/**
 * Cancels and joins the game loop thread to clean up resources.
 */
void clearGameLoopThread()
{
    pthread_cancel(gInstance.gameThread);     // Cancel the game loop thread
    pthread_join(gInstance.gameThread, NULL); // Wait for the thread to finish
}

/**
 * Cleans up and shuts down the graphics engine.
 */
void clearEngine()
{
    clearGameLoopThread(); // Clean up the game loop thread
    SDL_Quit();            // Shut down SDL
}

/**
 * Sets a pixel at (x, y) to the specified color.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color to set the pixel to.
 */
void pixel(int x, int y, unsigned int color)
{
    // Check if the coordinates are within screen bounds
    if (x < 0 || x >= gScreenWidth || y < 0 || y >= gScreenHeight)
        return;

    // Calculate the pixel index in the framebuffer
    register uint32_t pixelIndex = (y * gCorrectPixelsWidth) + x;

    // Set the pixel color
    framebuffer[pixelIndex] = color;
}

// Macro to update the screen with the current framebuffer contents
#define drawScreen() \
    SDL_Flip(gInstance.screen);

// Macro to fill the screen with black color
#define clearScreen() \
    SDL_FillRect(gInstance.screen, NULL, SDL_MapRGB(gInstance.screen->format, 0, 0, 0));

#endif