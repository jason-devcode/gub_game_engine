#ifndef JOYSTICK_INIT_POSSIBLE_RESULTS
#define JOYSTICK_INIT_POSSIBLE_RESULTS

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

#endif