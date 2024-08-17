#ifndef CONSTANT_MOUSE_EVENT_VALUES
#define CONSTANT_MOUSE_EVENT_VALUES

/**
 * @enum MouseEventType
 * @brief Enumeration of possible mouse event types.
 *
 * This enumeration defines the different types of mouse events that can be handled
 * by the EventManager.
 */
typedef enum
{
    // press events
    MOUSE_MOVE,                    /**< Event for mouse movement. */
    MOUSE_LEFT_BUTTON_PRESS,       /**< Event for mouse left button press. */
    MOUSE_MIDDLE_BUTTON_PRESS,     /**< Event for mouse middle button press. */
    MOUSE_RIGHT_BUTTON_PRESS,      /**< Event for mouse right button press. */
    MOUSE_WHEEL_UP_BUTTON_PRESS,   /**< Event for mouse wheel up press. */
    MOUSE_WHEEL_DOWN_BUTTON_PRESS, /**< Event for mouse wheel down press. */
    TOUCH_RIGHT_BUTTON_PRESS,      /**< Event for touch panel right side press. */
    TOUCH_LEFT_BUTTON_PRESS,       /**< Event for touch panel left side press. */

    // releaase events
    MOUSE_LEFT_BUTTON_RELEASE,       /**< Event for mouse left button release. */
    MOUSE_MIDDLE_BUTTON_RELEASE,     /**< Event for mouse middle button release. */
    MOUSE_RIGHT_BUTTON_RELEASE,      /**< Event for mouse right button release. */
    MOUSE_WHEEL_UP_BUTTON_RELEASE,   /**< Event for mouse wheel up release. */
    MOUSE_WHEEL_DOWN_BUTTON_RELEASE, /**< Event for mouse wheel down release. */
    TOUCH_RIGHT_BUTTON_RELEASE,      /**< Event for touch panel right side release. */
    TOUCH_LEFT_BUTTON_RELEASE,       /**< Event for touch panel left side release. */
    MOUSE_LAST = 20                  /** this is greater than the total mouse events registred here for avoid errors in mouse with more buttons  */
} MouseEventType;

#endif