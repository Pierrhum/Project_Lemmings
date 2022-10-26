#pragma once

#include "Element.h"
#include "Lemming.h"
#include "Animation.h"

#include <windows.h>
#include <vector>

#include "NYTimer.h"
#include "SkillButton.h"
#include "UIButton.h"

enum Hexa_color
{
    BLACK = 0, BLUE = 1, GREEN = 2, BLUESKY = 3, RED = 4, PURPLE = 5, YELLOW = 6, GREY_LIGHT = 7, GREY = 8,
    BLUE_LIGHT = 9, GREEN_LIGHT = 10, BLUESKY_LIGHT = 11, RED_LIGHT = 12, PURPLE_LIGHT = 13, YELLOW_LIGHT = 14, WHITE = 15
};

class DrawLemming
{
public:
    DrawLemming() :
    Play(new Animation("spriteAscii/button/playButton.txt", 1), COORD{130, 50}, UIButton::PLAY),
    dig_button(DIG_BUTTON, COORD{0, 84}),
    drop(new Animation("spriteAscii/drop/drop16.txt", 10), COORD{50, 20}, false),
    door(new Animation("spriteAscii/door/door16.txt", 6), COORD{110, 67}, true), // 145,67
    intial_level("spriteAscii/background/background200_100.txt"),
    title_screen("spriteAscii/background/lemmings_title_screen.txt")
    {
        short borderMap = (short)intial_level.w_picture;
        minute = Element(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 23), 5}, false);
        sec1 = Element(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 15), 5}, false);
        sec2 = Element(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 10), 5}, false);
        _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8));
        _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8, true));
        _anims.push_back( new Animation("spriteAscii/lemming_fall/lem_fall_size8.txt", 4));
        _anims.push_back( new Animation("spriteAscii/lemming_dig/lem_dig_size10.txt", 16));
        _anims.push_back( new Animation("spriteAscii/lemming_end/lem_end10.txt", 8));
        _anims.push_back( new Animation("spriteAscii/boom/lem_boom_size10.txt", 12));
        COORD centre_drop_lem{(short)(drop.get_center().X - _anims.at(2)->get_frame(0).w_picture/2), (short)(drop.get_center().Y - _anims.at(2)->get_frame(0).h_picture/2)};

        Lemming lem = Lemming(_anims, centre_drop_lem, FALL);
        lemmings.resize(10, Lemming(_anims, centre_drop_lem, FALL));        
    }
    
    static DrawLemming& Instance() {
        static DrawLemming S;
        return S;
    }
    bool is_title_screen = true;
    Picture intial_level;
    Picture title_screen;
    UIButton Play;
    vector<Lemming> lemmings;
    vector<Animation*> _anims;
    
    SkillButton dig_button;
    Element drop;
    Element door;
    Element minute;
    Element sec1;
    Element sec2;
    void DrawPixel(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Hexa_color color);
    void DrawPicture(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Picture picture, bool debugOutline=false);
    void Refresh_level(std::vector<std::vector<CHAR_INFO>>& buffer);
    void DisplayScreen(std::vector<std::vector<CHAR_INFO>>& buffer);
    void DrawLemmings(std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer& timer);

    bool isLevelEnded();
};
