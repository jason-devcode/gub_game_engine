#ifndef JOY_EVENT_MANAGER_H
#define JOY_EVEMT_MANAGER_H

#include "event_manager.h"

static int maxJoysticks = 2;

/**
 * @enum JoystickEventTypes
 * @brief Enum representing different types of joystick events.
 *
 * This enum defines various joystick button press and release events, hat motion events,
 * and axis motion events. It also includes padding events for safe memory allocation.
 */
typedef enum
{
    JOY_BUTTON_0_PRESS,  ///< A Button
    JOY_BUTTON_1_PRESS,  ///< B Button
    JOY_BUTTON_2_PRESS,  ///< X Button
    JOY_BUTTON_3_PRESS,  ///< Y Button
    JOY_BUTTON_4_PRESS,  ///< L1 Button
    JOY_BUTTON_5_PRESS,  ///< R1 Button
    JOY_BUTTON_6_PRESS,  ///< Select Button
    JOY_BUTTON_7_PRESS,  ///< Start Button
    JOY_BUTTON_8_PRESS,  ///< Menu Button
    JOY_BUTTON_9_PRESS,  ///< L3 Button
    JOY_BUTTON_10_PRESS, ///< R3 Button
    // Extra buttons for other joypad layouts
    JOY_BUTTON_11_PRESS,
    JOY_BUTTON_12_PRESS,
    JOY_BUTTON_13_PRESS,
    JOY_BUTTON_14_PRESS,
    JOY_BUTTON_15_PRESS,
    JOY_BUTTON_16_PRESS,

    // Release button joy events
    JOY_BUTTON_0_RELEASE,  ///< A Button
    JOY_BUTTON_1_RELEASE,  ///< B Button
    JOY_BUTTON_2_RELEASE,  ///< X Button
    JOY_BUTTON_3_RELEASE,  ///< Y Button
    JOY_BUTTON_4_RELEASE,  ///< L1 Button
    JOY_BUTTON_5_RELEASE,  ///< R1 Button
    JOY_BUTTON_6_RELEASE,  ///< Select Button
    JOY_BUTTON_7_RELEASE,  ///< Start Button
    JOY_BUTTON_8_RELEASE,  ///< Menu Button
    JOY_BUTTON_9_RELEASE,  ///< L3 Button
    JOY_BUTTON_10_RELEASE, ///< R3 Button
    // Extra buttons for other joypad layouts
    JOY_BUTTON_11_RELEASE,
    JOY_BUTTON_12_RELEASE,
    JOY_BUTTON_13_RELEASE,
    JOY_BUTTON_14_RELEASE,
    JOY_BUTTON_15_RELEASE,
    JOY_BUTTON_16_RELEASE,
    JOY_HAT_MOTION,  ///< HAT Motion Event
    JOY_AXIS_MOTION, ///< Axis Motion Event
    // Ignore this, just for safe memory allocation
    JOY_PADDING_1_EVENT,
    JOY_PADDING_2_EVENT,
    JOY_PADDING_3_EVENT,
    JOY_LAST_EVENT ///< Marker for the last event type
} JoystickEventTypes;

// Max count of listener lists for several joysticks
#define MAX_JOYSTICK_LISTENER_LISTS_COUNT (JOY_LAST_EVENT * maxJoysticks)

enum
{
    JOSTICK_PLAYER_1,
    JOSTICK_PLAYER_2,
    // JOSTICK_PLAYER_3,
    // JOSTICK_PLAYER_4,
} JoystickIndices;

/**
 * @var gJoyStickEventManager
 * @brief Global event manager for joystick events.
 *
 * Manages joystick event listeners and triggers events.
 */
static EventManager gJoyStickEventManager = {NULL, 0};

/**
 * @brief Initializes the joystick event manager.
 *
 * Sets up the event manager for handling joystick events by allocating necessary resources.
 *
 * @return true if initialization is successful, false otherwise.
 */
bool initializeJoystickEventManager()
{
    return initializeEventManager(&gJoyStickEventManager, MAX_JOYSTICK_LISTENER_LISTS_COUNT);
}

/**
 * @brief Calculates the event type for a given joystick player and event type.
 *
 * @param eventType The joystick event type.
 * @param joystickPlayerId The ID of the joystick player.
 * @return The calculated event type as a 32-bit unsigned integer.
 */
#define CALCULATE_JOYPAD_EVENT_TYPE(eventType, joystickPlayerId) ((uint32_t)((eventType) + ((joystickPlayerId) * (JOY_LAST_EVENT))))

/**
 * @brief Adds an event listener for a specific joystick event type.
 *
 * Registers a listener to handle events of the specified type for a given joystick player.
 *
 * @param type The joystick event type.
 * @param joystickPlayerId The ID of the joystick player.
 * @param listener The event listener to add.
 */
#define addJoypadEventListener(type, joystickPlayerId, listener) \
    addEventListener(&gJoyStickEventManager, CALCULATE_JOYPAD_EVENT_TYPE(type, joystickPlayerId), (listener))

/**
 * @brief Removes an event listener for a specific joystick event type.
 *
 * Unregisters a listener from handling events of the specified type for a given joystick player.
 *
 * @param type The joystick event type.
 * @param joystickPlayerId The ID of the joystick player.
 * @param listener The event listener to remove.
 */
#define removeJoypadEventListener(type, joystickPlayerId, listener) \
    removeEventListener(&gJoyStickEventManager, CALCULATE_JOYPAD_EVENT_TYPE(type, joystickPlayerId), (listener))

#endif