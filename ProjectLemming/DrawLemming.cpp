#include "DrawLemming.h"

#include <fstream>
#include <string>

void DrawLemming::DrawPixel(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], int x, int y, Hexa_color color)
{
    int top_mask = 0xF0; int bot_mask = 0x0F;
    buffer[y/2][x].Attributes &= y%2 ? bot_mask : top_mask;
    buffer[y/2][x].Attributes += y%2 ? color<<4 : color;
    
    buffer[y/2][x].Char.UnicodeChar = 0x2580;
}

void DrawLemming::DrawPicture(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], int x, int y, Picture picture)
{
    for (int i = 0; i < picture.h_picture*picture.w_picture; ++i)
    {
        Instance().DrawPixel(buffer, x + i%picture.w_picture, y + i/picture.w_picture, (Hexa_color)picture.vpicture.at(i));
    }
}