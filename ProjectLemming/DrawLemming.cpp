#include "DrawLemming.h"

#include <tchar.h>

void DrawLemming::DrawPixel(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Hexa_color color)
{
    if(y/2 >= buffer.size() || x >= buffer[0].size()) return;
    
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
        DrawPixel(buffer, x + i%picture.w_picture, y + i/picture.w_picture, (Hexa_color)picture.get_pixel(i));
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

void DrawLemming::Refresh_level(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawPicture(buffer, 0, 0, intial_level);
    drop.play_next_frame(buffer);
    door.play_next_frame(buffer);
    dig_button.ShowButton(buffer);
}

void DrawLemming::DisplayScreen(std::vector<std::vector<CHAR_INFO>>& buffer)
{
    DrawPicture(buffer, 0, 0, title_screen);
}

void DrawLemming::DrawLemmings(std::vector<std::vector<CHAR_INFO>> &buffer, NYTimer& timer)
{
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).is_showed)
        {
            lemmings.at(i).Update(buffer);
            if(lemmings.at(i).isOverlapping(door, true)) lemmings.at(i).exitLevel();
        }
    
    // Gestion du timer
    int _minute = timer.getRemainingTime() / 60;
    int _seconde = timer.getRemainingTime() - (_minute * 60);
    // Affichage
    minute.play_frame(buffer, _minute);
    sec1.play_frame(buffer, _seconde / 10);
    sec2.play_frame(buffer, _seconde % 10);
}

bool DrawLemming::isLevelEnded()
{
    bool ended = true;
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).current_state != END) ended = false;

    return ended;
}
