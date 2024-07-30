#ifndef COLOR_UTILS
#define COLOR_UTILS

#include "byte.h"

#define GETA(color) (EXTRACT_BYTE(color, 3))
#define GETR(color) (EXTRACT_BYTE(color, 2))
#define GETG(color) (EXTRACT_BYTE(color, 1))
#define GETB(color) (EXTRACT_BYTE(color, 0))

#define RGB(r, g, b) (INSERT_BYTE(0xFF, 3) | INSERT_BYTE(r, 2) | INSERT_BYTE(g, 1) | INSERT_BYTE(b, 0))
#define RGBA(r, g, b, a) (INSERT_BYTE(a, 3) | INSERT_BYTE(r, 2) | INSERT_BYTE(g, 1) | INSERT_BYTE(b, 0))

#endif