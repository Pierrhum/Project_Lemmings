#pragma once
#include <windows.h>
#include "Picture.h"

enum Hexa_color
{
    BLACK = 0, BLUE = 1, GREEN = 2, BLUESKY = 3, RED = 4, PURPLE = 5, YELLOW = 6, GREY_LIGHT = 7, GREY = 8,
    BLUE_LIGHT = 9, GREEN_LIGHT = 10, BLUESKY_LIGHT = 11, RED_LIGHT = 12, PURPLE_LIGHT = 13, YELLOW_LIGHT = 14, WHITE = 15
};

class DrawLemming
{
public:
    DrawLemming(){};
    static DrawLemming& Instance() {
        static DrawLemming S;
        return S;
    }
    Picture intial_level;
    void DrawPixel(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Hexa_color color);
    void DrawPicture(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Picture picture);
};
