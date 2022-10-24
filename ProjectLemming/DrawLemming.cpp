#include "DrawLemming.h"

WORD DrawLemming::ColorToAttribute(Hexa_color color)
{
    WORD Attribute = 0x0000;
    int top_mask = 0xF0; int bot_mask = 0x0F;
    /*
    if (color != -1)
    {
        Attribute &= y%2 ? bot_mask : top_mask;
        Attribute += y%2 ? color<<4 : color;
    }*/

    return Attribute;
}

void DrawLemming::DrawPixel(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Hexa_color color)
{
    
    int top_mask = 0xF0; int bot_mask = 0x0F;
    if(y > 97) return;
    if (color != -1)
    {
        buffer[y/2][x].Attributes &= y%2 ? bot_mask : top_mask;
        buffer[y/2][x].Attributes += y%2 ? color<<4 : color;
    }

    buffer[y/2][x].Char.UnicodeChar = 0x2580;
}

void DrawLemming::DrawPicture(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Picture picture, bool debugOutline)
{
    for (int i = 0; i < picture.h_picture*picture.w_picture; ++i)
    {
        Instance().DrawPixel(buffer, x + i%picture.w_picture, y + i/picture.w_picture, (Hexa_color)picture.get_pixel(i));
    }
    
    if(debugOutline)
    {
        for(int h = y; h < y + picture.h_picture; ++h)
        {
            Instance().DrawPixel(buffer, x, h, RED);
            Instance().DrawPixel(buffer, x + picture.w_picture, h, RED);            
        }
        for(int w = x; w < x + picture.w_picture; ++w)
        {
            Instance().DrawPixel(buffer, w, y, RED);
            Instance().DrawPixel(buffer, w, y + picture.h_picture, RED);            
        }
    }
}

void DrawLemming::Refresh_init_level(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    Instance().DrawPicture(buffer, 0, 0, intial_level);
}