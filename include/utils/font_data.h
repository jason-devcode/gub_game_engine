#ifndef FONT_DATA
#define FONT_DATA
#include <stdint.h>

const uint8_t font_data[256 * 8] = {
    #include "font_data/font_bitmap_table.h"
};

#endif