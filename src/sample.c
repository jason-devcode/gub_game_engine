#include "../include/graphic_engine.h" // Includes the custom graphics engine header
#include "../include/geometry.h"
#include "../include/utils/color.h"

/**
 * The game loop function that continuously updates the screen.
 *
 * @param arg A pointer to any arguments passed to the thread (not used here).
 * @return Returns NULL (the thread function return type must be void*).
 */
void *gameLoop(void *arg)
{
    do
    {
        clearScreen(); // Clears the screen with a black color

        drawCircle(256, 256, 64, RGB(255,0,0));

        drawScreen();
        SDL_Delay(16); 
    } while (ON_GAME_RUNNING); 
    return NULL;
}

/**
 * Main function to initialize, run, and clean up the graphics engine.
 *
 * @return Returns EXIT_SUCCESS to indicate successful completion.
 */
int main()
{
    // Initialize the graphics engine with a screen size of 512x512 and a window title
    initGraphicEngine(512, 512, "Basic SDL Engine");

    // Initialize the game loop with the gameLoop function
    initializeGameLoop(gameLoop);

    // Run the main engine loop, which handles events and updates the screen
    runEngine();

    // Clean up resources and shut down the engine
    clearEngine();

    return EXIT_SUCCESS; // Return success exit code
}