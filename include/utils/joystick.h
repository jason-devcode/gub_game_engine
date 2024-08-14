#ifndef JOYSTICK_UTILS_H
#define JOYSTICK_UTILS_H

#include <SDL/SDL.h> // SDL library for handling joystick input
#include <stdbool.h> // Boolean type support
#include <stdio.h>   // Standard I/O operations
#include <string.h>  // String operations

#include "../core/managers/joystick_event_manager.h" // event manager for joystick events
#include "fast_math/fast_abs.h"

// Define maximum axis value for normalization. The range is adjusted by 0.5 to fix the range to [-32767.5, 32767.5]
#define MAX_AXIS_VALUE 32767.5

// Enumeration representing different joystick axis types
enum JoystickAxisTypes
{
    LEFT_AXIS_X,           // Left stick X-axis
    LEFT_AXIS_Y,           // Left stick Y-axis
    RIGHT_AXIS_X = 3,      // Right stick X-axis (starting from index 3)
    RIGHT_AXIS_Y,          // Right stick Y-axis
    LEFT_TRIGGER_AXIS = 2, // Left trigger axis (L2 or LT button)
    RIGHT_TRIGGER_AXIS = 5 // Right trigger axis (R2 or RT button)
};

// Structure to store the state of the joystick axes and hat switch
typedef struct _tag_joystick_state_
{
    double motionLeftAxisX; // Motion value of left stick X-axis
    double motionLeftAxisY; // Motion value of left stick Y-axis

    double motionRightAxisX; // Motion value of right stick X-axis
    double motionRightAxisY; // Motion value of right stick Y-axis

    double motionLeftTriggerAxis;  // Motion value of left trigger axis
    double motionRightTriggerAxis; // Motion value of right trigger axis

    double motionHatX; // Motion value of hat switch X-axis
    double motionHatY; // Motion value of hat switch Y-axis
} JoystickState;

// Global variables
SDL_Joystick **gJoysticks; // Array of pointers to SDL joystick objects

JoystickState *gJoysticksCurrentState; // Array to store the current state of all joysticks

static int gJoystickAxisDeadzone = 20000; // Deadzone threshold for joystick axis motion

static bool *gJoystickButtonsPressed = NULL; // Array to track the pressed state of joystick buttons

// Enumeration representing possible results from joystick initialization
enum JoystickInitPossibleResults
{
    NOT_FOUND_JOYSTICK,                                     // No joystick found
    COULD_NOT_OPEN_JOYSTICK,                                // Could not open joystick
    CANNOT_INITIALIZE_JOYSTICK_SUBSYSTEM,                   // Failed to initialize SDL joystick subsystem
    CANNOT_INITIALIZE_JOYSTICK_EVENT_MANAGER,               // Failed to initialize the joystick event manager
    CANNOT_ALLOC_MEMORY_FOR_JOYSTICKS_STRUCTURES,           // Failed to allocate memory for joystick structures
    CANNOT_ALLOC_MEMORY_FOR_JOYSTICKS_CURRENT_STATE,        // Failed to allocate memory for joystick state array
    CANNOT_ALLOC_MEMORY_FOR_JOYSTICKS_PRESSED_BUTTON_FLAGS, // Failed to allocate memory for joystick button flags
    SUCCESS_INIT_JOYSTICK_SYSTEM                            // Successful initialization
};

/**
 * @brief Initializes the array to hold the current state of all joysticks.
 *
 * @return true if the array is successfully allocated and initialized, false otherwise.
 */
bool initJoystickCurrentStateArray()
{

    gJoysticksCurrentState = (JoystickState *)malloc(sizeof(JoystickState[maxJoysticks]));

    if (!gJoysticksCurrentState)
        return false;

    memset(gJoysticksCurrentState, 0, sizeof(JoystickState[maxJoysticks]));

    return true;
}

/**
 * @brief Releases the memory allocated for the joystick current state array.
 */
void releaseJoysticksCurrentStateArray()
{
    if (!gJoysticksCurrentState)
        return;
    free(gJoysticksCurrentState);
    gJoysticksCurrentState = NULL;
}

/**
 * @brief Initializes the array to hold the pressed state of joystick buttons.
 *
 * @return true if the array is successfully allocated and initialized, false otherwise.
 */
bool initJoystickButtonsPressedFlagsArray()
{
    gJoystickButtonsPressed = (bool *)malloc(sizeof(bool[MAX_JOYSTICK_LISTENER_LISTS_COUNT]));

    if (!gJoystickButtonsPressed)
        return false;

    memset(gJoystickButtonsPressed, 0, sizeof(bool[MAX_JOYSTICK_LISTENER_LISTS_COUNT]));

    return true;
}

/**
 * @brief Releases the memory allocated for the joystick buttons pressed flags array.
 */
void releaseJoystickButtonsPressedFlagsArray()
{
    if (!gJoystickButtonsPressed)
        return;
    free(gJoystickButtonsPressed);
    gJoystickButtonsPressed = NULL;
}

/**
 * @brief Initializes the joystick manager, setting up the necessary structures and subsystems.
 *
 * @return An integer representing the result of the initialization. Refer to `JoystickInitPossibleResults` for possible values.
 */
int initializeJoystickManager()
{
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
    {
        fprintf(stderr, "Cannot initialize SDL Joystick subsystem: %s\n", SDL_GetError());
        return CANNOT_INITIALIZE_JOYSTICK_SUBSYSTEM;
    }

    if (!initJoystickCurrentStateArray())
    {
        fprintf(stderr, "Cannot allocate memory space for joysticks current state array \n");
        return CANNOT_ALLOC_MEMORY_FOR_JOYSTICKS_CURRENT_STATE;
    }

    if (!initJoystickButtonsPressedFlagsArray())
    {
        fprintf(stderr, "Cannot allocate memory space for joysticks button flags \n");
        return CANNOT_ALLOC_MEMORY_FOR_JOYSTICKS_PRESSED_BUTTON_FLAGS;
    }

    int numJoysticks = SDL_NumJoysticks();
    if (numJoysticks == 0)
    {
        fprintf(stderr, "No Joysticks found\n");
        return NOT_FOUND_JOYSTICK;
    }

    if (!initializeJoystickEventManager())
    {
        fprintf(stderr, "Cannot initialize joystick event manager");
        return CANNOT_INITIALIZE_JOYSTICK_EVENT_MANAGER;
    }

    // alloc space for joysticks
    gJoysticks = (SDL_Joystick **)malloc(sizeof(SDL_Joystick *[maxJoysticks]));

    if (!gJoysticks)
    {
        fprintf(stderr, "Cannot allocate memory space for joystick structures");
        return CANNOT_ALLOC_MEMORY_FOR_JOYSTICKS_STRUCTURES;
    }

    for (int i = 0; i < numJoysticks && i < maxJoysticks; i++)
    {
        gJoysticks[i] = SDL_JoystickOpen(i);
        if (gJoysticks[i] == NULL)
        {
            fprintf(stderr, "Couldn't open Joystick %d\n", i);
            if (i == 0)
            {
                free(gJoysticks);
                gJoysticks = NULL;
                return COULD_NOT_OPEN_JOYSTICK;
            }
            break; // Ignore the second joystick if it can't be opened
        }
    }

    return SUCCESS_INIT_JOYSTICK_SYSTEM;
}

/**
 * @brief Sets the deadzone value for joystick axes. Values below this threshold are considered zero.
 *
 * @param newDeadZoneValue The new deadzone value to set. Negative values are converted to positive.
 * @note recommend values greater than 15000 and less than 25000
 */
void setJoystickAxisDeadzone(int newDeadZoneValue)
{
    gJoystickAxisDeadzone = newDeadZoneValue < 0 ? -newDeadZoneValue : newDeadZoneValue;
}

/**
 * @brief Retrieves the current state of the specified joystick.
 *
 * @param index The index of the joystick to retrieve the state for.
 * @return A pointer to the `JoystickState` of the specified joystick, or NULL if the state array is not initialized.
 */
JoystickState *getJoystickState(int index)
{
    if (!gJoysticksCurrentState)
        return NULL;
    return &gJoysticksCurrentState[index];
}

/**
 * @brief Retrieves the name of the specified joystick.
 *
 * @param index The index of the joystick.
 * @return A string containing the name of the joystick, or NULL if the joystick is not found.
 */
const char *getJoystickName(int index)
{
    if (index >= 0 && index < maxJoysticks && gJoysticks[index] != NULL)
        return SDL_JoystickName(index);
    return NULL;
}

/**
 * @brief Retrieves the number of axes available on the specified joystick.
 *
 * @param index The index of the joystick.
 * @return The number of axes, or -1 if the joystick is not found.
 */
int getJoystickNumAxes(int index)
{
    if (gJoysticks && index >= 0 && index < maxJoysticks && gJoysticks[index] != NULL)
        return SDL_JoystickNumAxes(gJoysticks[index]);
    return -1;
}

/**
 * @brief Retrieves the number of buttons available on the specified joystick.
 *
 * @param index The index of the joystick.
 * @return The number of buttons, or -1 if the joystick is not found.
 */
int getJoystickNumButtons(int index)
{
    if (gJoysticks && index >= 0 && index < maxJoysticks && gJoysticks[index] != NULL)
        return SDL_JoystickNumButtons(gJoysticks[index]);
    return -1;
}

/**
 * @brief Retrieves the number of hats available on the specified joystick.
 *
 * @param index The index of the joystick.
 * @return The number of hats, or -1 if the joystick is not found.
 */
int getJoystickNumHats(int index)
{
    if (gJoysticks && index >= 0 && index < maxJoysticks && gJoysticks[index] != NULL)
        return SDL_JoystickNumHats(gJoysticks[index]);
    return -1;
}

/**
 * @brief Retrieves the number of balls available on the specified joystick.
 *
 * @param index The index of the joystick.
 * @return The number of balls, or -1 if the joystick is not found.
 */
int getJoystickNumBalls(int index)
{
    if (gJoysticks && index >= 0 && index < maxJoysticks && gJoysticks[index] != NULL)
        return SDL_JoystickNumBalls(gJoysticks[index]);
    return -1;
}

/**
 * @brief Processes joystick button press events.
 *
 * Updates the button pressed state and triggers the corresponding event.
 *
 * @param event A pointer to the SDL event structure containing the button press information.
 */
#define PROCESS_JOYSTICK_BUTTON_PRESSED(event)                          \
    int button = event->jbutton.button;                                 \
    int joystickIndex = event->jbutton.which;                           \
    int keyButton = CALCULATE_JOYPAD_EVENT_TYPE(button, joystickIndex); \
    if (!gJoystickButtonsPressed[keyButton])                            \
    {                                                                   \
        gJoystickButtonsPressed[keyButton] = true;                      \
        triggerEvent(gJoyStickEventManager, keyButton);                 \
    }

/**
 * @brief Processes joystick button release events.
 *
 * Updates the button released state and triggers the corresponding event.
 *
 * @param event A pointer to the SDL event structure containing the button release information.
 */
#define PROCESS_JOYSTICK_BUTTON_RELEASED(event)                                                                         \
    int button = event->jbutton.button;                                                                                 \
    int joystickIndex = event->jbutton.which;                                                                           \
    int keyButton = CALCULATE_JOYPAD_EVENT_TYPE(button, joystickIndex);                                                 \
    if (gJoystickButtonsPressed[keyButton])                                                                             \
    {                                                                                                                   \
        gJoystickButtonsPressed[keyButton] = false;                                                                     \
        triggerEvent(gJoyStickEventManager, CALCULATE_JOYPAD_EVENT_TYPE(button + JOY_BUTTON_0_RELEASE, joystickIndex)); \
    }

/**
 * @brief Triggers events for all pressed joystick buttons.
 *
 * Checks all button states and triggers events for those that are pressed.
 */
#define TRIGGER_PRESSED_JOYSTICKS_BUTTONS()                         \
    {                                                               \
        for (int i = 0; i < MAX_JOYSTICK_LISTENER_LISTS_COUNT; ++i) \
        {                                                           \
            if (gJoystickButtonsPressed[i])                         \
            {                                                       \
                triggerEvent(gJoyStickEventManager, i);             \
            }                                                       \
        }                                                           \
    }

/**
 * @brief Handles joystick events.
 *
 * Processes events related to joystick axis motion, hat motion, and button presses/releases.
 *
 * @param event A pointer to the SDL event structure containing joystick event information.
 */
void handleJoystickEvents(SDL_Event *event)
{
    if (!gJoysticks || gJoyStickEventManager.listsCount == 0)
        return;

    switch (event->type)
    {
    case SDL_JOYAXISMOTION:
    {
        int currentJoystickIndex = event->jaxis.which;
        JoystickState *currentJoystick = &gJoysticksCurrentState[currentJoystickIndex];

        // cast to double to fix value range
        double axisValue = (double)event->jaxis.value;

        //  + .5 to fix range [-32768,32767] to range [-32767.5,32767.5]
        axisValue += 0.5;

        // normalize axis value to range [-1,1]
        double normalizedAxisValue = axisValue / MAX_AXIS_VALUE;

        // use this to avoid extensive switch or else if conditions
        int axisType = event->jaxis.axis;
        int axisIndex =
            (axisType == 2) ? 4 : // condition for left trigger axis
                (axisType >= 3 && axisType < 5) ? (axisType - 1)
                                                : // condition for right X and Y axis
                axisType;                         // for right trigger axis;

        double *currentAxisPtr = &((double *)currentJoystick)[axisIndex];

        // if axis value is less than joystick axis deadzone break sentence
        if (fast_abs(axisValue) < gJoystickAxisDeadzone)
            *currentAxisPtr = 0;

        *currentAxisPtr = normalizedAxisValue;

        // printf("Joystick %d axis %d value: %lf\n", event->jaxis.which, axisIndex, normalizedAxisValue);
        break;
    }
    case SDL_JOYHATMOTION:
    {
        int currentJoystickIndex = event->jhat.which;
        JoystickState *currentJoystick = &gJoysticksCurrentState[currentJoystickIndex];

        switch (event->jhat.value)
        {
        case SDL_HAT_CENTERED:
            currentJoystick->motionHatX = 0;
            currentJoystick->motionHatY = 0;
            break;
        case SDL_HAT_UP:
            currentJoystick->motionHatX = 0;
            currentJoystick->motionHatY = -1;
            break;
        case SDL_HAT_RIGHT:
            currentJoystick->motionHatX = 1;
            currentJoystick->motionHatY = 0;
            break;
        case SDL_HAT_DOWN:
            currentJoystick->motionHatX = 0;
            currentJoystick->motionHatY = 1;
            break;
        case SDL_HAT_LEFT:
            currentJoystick->motionHatX = -1;
            currentJoystick->motionHatY = 0;
            break;
        case SDL_HAT_RIGHTUP:
            currentJoystick->motionHatX = 0.70711;
            currentJoystick->motionHatY = -0.70711;
            break;
        case SDL_HAT_RIGHTDOWN:
            currentJoystick->motionHatX = 0.70711;
            currentJoystick->motionHatY = 0.70711;
            break;
        case SDL_HAT_LEFTUP:
            currentJoystick->motionHatX = -0.70711;
            currentJoystick->motionHatY = -0.70711;
            break;
        case SDL_HAT_LEFTDOWN:
            currentJoystick->motionHatX = -0.70711;
            currentJoystick->motionHatY = 0.70711;
            break;
        }
        // printf("Joystick %d hat %d value: %d\n", event->jhat.which, event->jhat.hat, event->jhat.value);
        break;
    }
    case SDL_JOYBUTTONDOWN:
    {
        PROCESS_JOYSTICK_BUTTON_PRESSED(event);
    }
    break;

    case SDL_JOYBUTTONUP:
    {
        PROCESS_JOYSTICK_BUTTON_RELEASED(event);
    }
    break;
    }

    // TRIGGER_PRESSED_JOYSTICKS_BUTTONS();
}

/**
 * @brief Closes all joysticks and cleans up resources.
 *
 * Closes open joysticks, releases allocated memory, and shuts down the SDL joystick subsystem.
 */
void closeJoystickManager()
{
    if (!gJoysticks)
        goto close_sdl_joystick_subsystem;

    for (int joystickIterator = 0; joystickIterator < maxJoysticks; joystickIterator++)
    {
        if (gJoysticks[joystickIterator] != NULL)
        {
            SDL_JoystickClose(gJoysticks[joystickIterator]);
            gJoysticks[joystickIterator] = NULL;
        }
    }
    free(gJoysticks);
    gJoysticks = NULL;
close_sdl_joystick_subsystem:
    releaseJoysticksCurrentStateArray();
    releaseJoystickButtonsPressedFlagsArray();
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

#endif
