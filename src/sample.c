#include "../include/graphic_engine.h" // Includes the custom graphics engine header

// use r*r = x*x + y*y circle formula for find points inside the circle
void drawCircle(int cx, int cy, int radius, uint32_t color)
{
    for (int Y = -radius; Y < radius; ++Y)
    {
        for (int X = -radius; X < radius; ++X)
        {
            if ((X * X + Y * Y) < radius * radius) // if the point is inside of the circle
            {
                pixel(X+cx, Y+cy, color);
            }
        }
    }
}

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

        drawCircle( 256, 256, 64, 0xFFFF0000 );

        drawScreen();  // Update the screen with the current framebuffer contents
        SDL_Delay(16); // Delay to maintain approximately 60 FPS
    } while (true); // Infinite loop to keep the game running
    return NULL; // Return NULL as required by the thread function signature
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