#include "../include/gub.h"

#include "../include/utils/color.h"
#include "../include/utils/geometry.h"
#include "../include/utils/color_palette.h"

typedef struct _tag_color_picker_component_
{
    int x, y, cellWidth, cellHeight;
    int colorSelected, shadeSelected;
} ColorPicker;

ColorPicker *createColorPicker(int x, int y, int cellWidth, int cellHeight)
{
    ColorPicker *colorPicker = (ColorPicker *)malloc(sizeof(ColorPicker));
    colorPicker->x = x;
    colorPicker->y = y;
    colorPicker->cellWidth = cellWidth;
    colorPicker->cellHeight = cellHeight;
    return colorPicker;
}

void drawColorPicker(ColorPicker *colorPicker)
{
}

int gameLoop(void *ignore)
{
    do
    {
        clearScreen();

        drawScreen();
        renderDelay(16);
    } while (isGameRunning);

    return NULL;
}

CREATE_GAME(640, 640, "Sprite Editor")