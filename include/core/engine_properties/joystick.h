#ifndef JOYSTICK_ENGINE_PROPERTIES_H
#define JOYSTICK_ENGINE_PROPERTIES_H

#include <stdbool.h>
#include <stdlib.h>

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

JoystickState *gJoysticksCurrentState; // Array to store the current state of all joysticks

static int gJoystickAxisDeadzone = 20000; // Deadzone threshold for joystick axis motion

static bool *gJoystickButtonsPressed = NULL; // Array to track the pressed state of joystick buttons

static int maxJoysticks = 2;

#endif