#ifndef JOYSTICK_AXIS_TYPES
#define JOYSTICK_AXIS_TYPES

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

#endif