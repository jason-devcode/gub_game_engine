#ifndef KEY_EVENT_VALUES_H
#define KEY_EVENT_VALUES_H

#ifdef USE_SDL_2

#include <SDL2/SDL_keycode.h>

// Numbers
#define GUB_KEY_0 SDLK_0
#define GUB_KEY_1 SDLK_1
#define GUB_KEY_2 SDLK_2
#define GUB_KEY_3 SDLK_3
#define GUB_KEY_4 SDLK_4
#define GUB_KEY_5 SDLK_5
#define GUB_KEY_6 SDLK_6
#define GUB_KEY_7 SDLK_7
#define GUB_KEY_8 SDLK_8
#define GUB_KEY_9 SDLK_9

// Letters
#define GUB_KEY_a SDLK_a
#define GUB_KEY_b SDLK_b
#define GUB_KEY_c SDLK_c
#define GUB_KEY_d SDLK_d
#define GUB_KEY_e SDLK_e
#define GUB_KEY_f SDLK_f
#define GUB_KEY_g SDLK_g
#define GUB_KEY_h SDLK_h
#define GUB_KEY_i SDLK_i
#define GUB_KEY_j SDLK_j
#define GUB_KEY_k SDLK_k
#define GUB_KEY_l SDLK_l
#define GUB_KEY_m SDLK_m
#define GUB_KEY_n SDLK_n
#define GUB_KEY_o SDLK_o
#define GUB_KEY_p SDLK_p
#define GUB_KEY_q SDLK_q
#define GUB_KEY_r SDLK_r
#define GUB_KEY_s SDLK_s
#define GUB_KEY_t SDLK_t
#define GUB_KEY_u SDLK_u
#define GUB_KEY_v SDLK_v
#define GUB_KEY_w SDLK_w
#define GUB_KEY_x SDLK_x
#define GUB_KEY_y SDLK_y
#define GUB_KEY_z SDLK_z

// Symbols and other chars
#define GUB_KEY_MINUS SDLK_MINUS               // -
#define GUB_KEY_EQUALS SDLK_EQUALS             // =
#define GUB_KEY_LEFTBRACKET SDLK_LEFTBRACKET   // [
#define GUB_KEY_RIGHTBRACKET SDLK_RIGHTBRACKET // ]
#define GUB_KEY_BACKSLASH SDLK_BACKSLASH       // \ 
#define GUB_KEY_SEMICOLON SDLK_SEMICOLON    // ;
#define GUB_KEY_APOSTROPHE SDLK_APOSTROPHE     // '
#define GUB_KEY_GRAVE SDLK_GRAVE               // `
#define GUB_KEY_COMMA SDLK_COMMA               // ,
#define GUB_KEY_PERIOD SDLK_PERIOD             // .
#define GUB_KEY_SLASH SDLK_SLASH               // /
#define GUB_KEY_CAPSLOCK SDLK_CAPSLOCK         // Caps Lock

// Functions
#define GUB_KEY_F1 SDLK_F1
#define GUB_KEY_F2 SDLK_F2
#define GUB_KEY_F3 SDLK_F3
#define GUB_KEY_F4 SDLK_F4
#define GUB_KEY_F5 SDLK_F5
#define GUB_KEY_F6 SDLK_F6
#define GUB_KEY_F7 SDLK_F7
#define GUB_KEY_F8 SDLK_F8
#define GUB_KEY_F9 SDLK_F9
#define GUB_KEY_F10 SDLK_F10
#define GUB_KEY_F11 SDLK_F11
#define GUB_KEY_F12 SDLK_F12

// Control
#define GUB_KEY_BACKSPACE SDLK_BACKSPACE
#define GUB_KEY_TAB SDLK_TAB
#define GUB_KEY_RETURN SDLK_RETURN
#define GUB_KEY_ESCAPE SDLK_ESCAPE
#define GUB_KEY_SPACE SDLK_SPACE

// Key modifiers
#define GUB_KEY_LSHIFT SDLK_LSHIFT
#define GUB_KEY_RSHIFT SDLK_RSHIFT
#define GUB_KEY_LCTRL SDLK_LCTRL
#define GUB_KEY_RCTRL SDLK_RCTRL
#define GUB_KEY_LALT SDLK_LALT
#define GUB_KEY_RALT SDLK_RALT
#define GUB_KEY_LGUI SDLK_LGUI
#define GUB_KEY_RGUI SDLK_RGUI

// Numpad
#define GUB_KEY_KP_0 SDLK_KP_0
#define GUB_KEY_KP_1 SDLK_KP_1
#define GUB_KEY_KP_2 SDLK_KP_2
#define GUB_KEY_KP_3 SDLK_KP_3
#define GUB_KEY_KP_4 SDLK_KP_4
#define GUB_KEY_KP_5 SDLK_KP_5
#define GUB_KEY_KP_6 SDLK_KP_6
#define GUB_KEY_KP_7 SDLK_KP_7
#define GUB_KEY_KP_8 SDLK_KP_8
#define GUB_KEY_KP_9 SDLK_KP_9
#define GUB_KEY_KP_ENTER SDLK_KP_ENTER
#define GUB_KEY_KP_PLUS SDLK_KP_PLUS         // +
#define GUB_KEY_KP_MINUS SDLK_KP_MINUS       // -
#define GUB_KEY_KP_MULTIPLY SDLK_KP_MULTIPLY // *
#define GUB_KEY_KP_DIVIDE SDLK_KP_DIVIDE     // /
#define GUB_KEY_KP_PERIOD SDLK_KP_PERIOD     // .

// Arrows
#define GUB_KEY_UP SDLK_UP
#define GUB_KEY_DOWN SDLK_DOWN
#define GUB_KEY_LEFT SDLK_LEFT
#define GUB_KEY_RIGHT SDLK_RIGHT

// Others
#define GUB_KEY_INSERT SDLK_INSERT
#define GUB_KEY_HOME SDLK_HOME
#define GUB_KEY_PAGEUP SDLK_PAGEUP
#define GUB_KEY_PAGEDOWN SDLK_PAGEDOWN
#define GUB_KEY_DELETE SDLK_DELETE
#define GUB_KEY_END SDLK_END

#elif USE_SDL_1

#include <SDL/SDL_keysym.h>

// Numbers
#define GUB_KEY_0 SDLK_0
#define GUB_KEY_1 SDLK_1
#define GUB_KEY_2 SDLK_2
#define GUB_KEY_3 SDLK_3
#define GUB_KEY_4 SDLK_4
#define GUB_KEY_5 SDLK_5
#define GUB_KEY_6 SDLK_6
#define GUB_KEY_7 SDLK_7
#define GUB_KEY_8 SDLK_8
#define GUB_KEY_9 SDLK_9

// Letters
#define GUB_KEY_a SDLK_a
#define GUB_KEY_b SDLK_b
#define GUB_KEY_c SDLK_c
#define GUB_KEY_d SDLK_d
#define GUB_KEY_e SDLK_e
#define GUB_KEY_f SDLK_f
#define GUB_KEY_g SDLK_g
#define GUB_KEY_h SDLK_h
#define GUB_KEY_i SDLK_i
#define GUB_KEY_j SDLK_j
#define GUB_KEY_k SDLK_k
#define GUB_KEY_l SDLK_l
#define GUB_KEY_m SDLK_m
#define GUB_KEY_n SDLK_n
#define GUB_KEY_o SDLK_o
#define GUB_KEY_p SDLK_p
#define GUB_KEY_q SDLK_q
#define GUB_KEY_r SDLK_r
#define GUB_KEY_s SDLK_s
#define GUB_KEY_t SDLK_t
#define GUB_KEY_u SDLK_u
#define GUB_KEY_v SDLK_v
#define GUB_KEY_w SDLK_w
#define GUB_KEY_x SDLK_x
#define GUB_KEY_y SDLK_y
#define GUB_KEY_z SDLK_z

// Symbols and other chars
#define GUB_KEY_MINUS SDLK_MINUS               // -
#define GUB_KEY_EQUALS SDLK_EQUALS             // =
#define GUB_KEY_LEFTBRACKET SDLK_LEFTBRACKET   // [
#define GUB_KEY_RIGHTBRACKET SDLK_RIGHTBRACKET // ]
#define GUB_KEY_BACKSLASH SDLK_BACKSLASH       // \ 
#define GUB_KEY_SEMICOLON SDLK_SEMICOLON       // ;
#define GUB_KEY_APOSTROPHE SDLK_QUOTE          // '
#define GUB_KEY_GRAVE SDLK_BACKQUOTE           // `
#define GUB_KEY_COMMA SDLK_COMMA               // ,
#define GUB_KEY_PERIOD SDLK_PERIOD             // .
#define GUB_KEY_SLASH SDLK_SLASH               // /
#define GUB_KEY_CAPSLOCK SDLK_CAPSLOCK         // Caps Lock

// Functions
#define GUB_KEY_F1 SDLK_F1
#define GUB_KEY_F2 SDLK_F2
#define GUB_KEY_F3 SDLK_F3
#define GUB_KEY_F4 SDLK_F4
#define GUB_KEY_F5 SDLK_F5
#define GUB_KEY_F6 SDLK_F6
#define GUB_KEY_F7 SDLK_F7
#define GUB_KEY_F8 SDLK_F8
#define GUB_KEY_F9 SDLK_F9
#define GUB_KEY_F10 SDLK_F10
#define GUB_KEY_F11 SDLK_F11
#define GUB_KEY_F12 SDLK_F12

// Control
#define GUB_KEY_BACKSPACE SDLK_BACKSPACE
#define GUB_KEY_TAB SDLK_TAB
#define GUB_KEY_RETURN SDLK_RETURN
#define GUB_KEY_ESCAPE SDLK_ESCAPE
#define GUB_KEY_SPACE SDLK_SPACE

// Modifiers
#define GUB_KEY_LSHIFT SDLK_LSHIFT
#define GUB_KEY_RSHIFT SDLK_RSHIFT
#define GUB_KEY_LCTRL SDLK_LCTRL
#define GUB_KEY_RCTRL SDLK_RCTRL
#define GUB_KEY_LALT SDLK_LALT
#define GUB_KEY_RALT SDLK_RALT
#define GUB_KEY_LMETA SDLK_LMETA
#define GUB_KEY_RMETA SDLK_RMETA

// Numpad
#define GUB_KEY_KP_0 SDLK_KP0
#define GUB_KEY_KP_1 SDLK_KP1
#define GUB_KEY_KP_2 SDLK_KP2
#define GUB_KEY_KP_3 SDLK_KP3
#define GUB_KEY_KP_4 SDLK_KP4
#define GUB_KEY_KP_5 SDLK_KP5
#define GUB_KEY_KP_6 SDLK_KP6
#define GUB_KEY_KP_7 SDLK_KP7
#define GUB_KEY_KP_8 SDLK_KP8
#define GUB_KEY_KP_9 SDLK_KP9
#define GUB_KEY_KP_ENTER SDLK_KP_ENTER
#define GUB_KEY_KP_PLUS SDLK_KP_PLUS         // +
#define GUB_KEY_KP_MINUS SDLK_KP_MINUS       // -
#define GUB_KEY_KP_MULTIPLY SDLK_KP_MULTIPLY // *
#define GUB_KEY_KP_DIVIDE SDLK_KP_DIVIDE     // /
#define GUB_KEY_KP_PERIOD SDLK_KP_PERIOD     // .

// Arrows
#define GUB_KEY_UP SDLK_UP
#define GUB_KEY_DOWN SDLK_DOWN
#define GUB_KEY_LEFT SDLK_LEFT
#define GUB_KEY_RIGHT SDLK_RIGHT

// Others
#define GUB_KEY_INSERT SDLK_INSERT
#define GUB_KEY_HOME SDLK_HOME
#define GUB_KEY_PAGEUP SDLK_PAGEUP
#define GUB_KEY_PAGEDOWN SDLK_PAGEDOWN
#define GUB_KEY_DELETE SDLK_DELETE
#define GUB_KEY_END SDLK_END

#else // DEFAULT MACROS FOR SYNTAX INTELLISENSE

// Numbers
#define GUB_KEY_0 '0'
#define GUB_KEY_1 '1'
#define GUB_KEY_2 '2'
#define GUB_KEY_3 '3'
#define GUB_KEY_4 '4'
#define GUB_KEY_5 '5'
#define GUB_KEY_6 '6'
#define GUB_KEY_7 '7'
#define GUB_KEY_8 '8'
#define GUB_KEY_9 '9'

// Letters
#define GUB_KEY_a 'a'
#define GUB_KEY_b 'b'
#define GUB_KEY_c 'c'
#define GUB_KEY_d 'd'
#define GUB_KEY_e 'e'
#define GUB_KEY_f 'f'
#define GUB_KEY_g 'g'
#define GUB_KEY_h 'h'
#define GUB_KEY_i 'i'
#define GUB_KEY_j 'j'
#define GUB_KEY_k 'k'
#define GUB_KEY_l 'l'
#define GUB_KEY_m 'm'
#define GUB_KEY_n 'n'
#define GUB_KEY_o 'o'
#define GUB_KEY_p 'p'
#define GUB_KEY_q 'q'
#define GUB_KEY_r 'r'
#define GUB_KEY_s 's'
#define GUB_KEY_t 't'
#define GUB_KEY_u 'u'
#define GUB_KEY_v 'v'
#define GUB_KEY_w 'w'
#define GUB_KEY_x 'x'
#define GUB_KEY_y 'y'
#define GUB_KEY_z 'z'

// Symbols and other chars
#define GUB_KEY_MINUS '-'
#define GUB_KEY_EQUALS '='
#define GUB_KEY_LEFTBRACKET '['
#define GUB_KEY_RIGHTBRACKET ']'
#define GUB_KEY_BACKSLASH '\\' 
#define GUB_KEY_SEMICOLON ';'
#define GUB_KEY_APOSTROPHE '\''
#define GUB_KEY_GRAVE '`'
#define GUB_KEY_COMMA ','
#define GUB_KEY_PERIOD '.'
#define GUB_KEY_SLASH '/'
#define GUB_KEY_CAPSLOCK 0  // Placeholder for Caps Lock

// Functions
#define GUB_KEY_F1 0 // Placeholder
#define GUB_KEY_F2 0 // Placeholder
#define GUB_KEY_F3 0 // Placeholder
#define GUB_KEY_F4 0 // Placeholder
#define GUB_KEY_F5 0 // Placeholder
#define GUB_KEY_F6 0 // Placeholder
#define GUB_KEY_F7 0 // Placeholder
#define GUB_KEY_F8 0 // Placeholder
#define GUB_KEY_F9 0 // Placeholder
#define GUB_KEY_F10 0 // Placeholder
#define GUB_KEY_F11 0 // Placeholder
#define GUB_KEY_F12 0 // Placeholder

// Control
#define GUB_KEY_BACKSPACE '\b'
#define GUB_KEY_TAB '\t'
#define GUB_KEY_RETURN '\r'
#define GUB_KEY_ESCAPE '\x1B'
#define GUB_KEY_SPACE ' '

// Key modifiers
#define GUB_KEY_LSHIFT 0 // Placeholder
#define GUB_KEY_RSHIFT 0 // Placeholder
#define GUB_KEY_LCTRL 0  // Placeholder
#define GUB_KEY_RCTRL 0  // Placeholder
#define GUB_KEY_LALT 0   // Placeholder
#define GUB_KEY_RALT 0   // Placeholder
#define GUB_KEY_LGUI 0   // Placeholder
#define GUB_KEY_RGUI 0   // Placeholder

// Numpad
#define GUB_KEY_KP_0 '0'
#define GUB_KEY_KP_1 '1'
#define GUB_KEY_KP_2 '2'
#define GUB_KEY_KP_3 '3'
#define GUB_KEY_KP_4 '4'
#define GUB_KEY_KP_5 '5'
#define GUB_KEY_KP_6 '6'
#define GUB_KEY_KP_7 '7'
#define GUB_KEY_KP_8 '8'
#define GUB_KEY_KP_9 '9'
#define GUB_KEY_KP_ENTER 0   // Placeholder
#define GUB_KEY_KP_PLUS '+'  // +
#define GUB_KEY_KP_MINUS '-' // -
#define GUB_KEY_KP_MULTIPLY '*' // *
#define GUB_KEY_KP_DIVIDE '/'   // /
#define GUB_KEY_KP_PERIOD '.'   // .

// Arrows
#define GUB_KEY_UP 0    // Placeholder
#define GUB_KEY_DOWN 0  // Placeholder
#define GUB_KEY_LEFT 0  // Placeholder
#define GUB_KEY_RIGHT 0 // Placeholder

// Others
#define GUB_KEY_INSERT 0  // Placeholder
#define GUB_KEY_HOME 0    // Placeholder
#define GUB_KEY_PAGEUP 0  // Placeholder
#define GUB_KEY_PAGEDOWN 0 // Placeholder
#define GUB_KEY_DELETE 0  // Placeholder
#define GUB_KEY_END 0     // Placeholder

#endif

#endif // KEY_EVENT_VALUES_H