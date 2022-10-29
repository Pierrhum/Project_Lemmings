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

enum ScreenEnum
{
    MENU, LEVEL_ONE, LEVEL_TWO, LEVEL_THREE, WIN, LOOSE
};

class DrawLemming
{
private:
    int nbLemmingToWin = 10;
public:
    DrawLemming() :
        title_screen("spriteAscii/background/lemmings_title_screen.txt"),
        level_one("spriteAscii/background/background_1_200_100.txt"),
        level_two("spriteAscii/background/background_2_200_100.txt"),
        level_three("spriteAscii/background/background_3_200_100.txt"),
        win_screen("spriteAscii/background/winlemmings200_100.txt"),
        lose_screen("spriteAscii/background/loselemmings200_100.txt"),
        Quit(new Animation("spriteAscii/button/quitButton.txt", 1), COORD{180, 55}, UIButton::QUIT),
        Play(new Animation("spriteAscii/button/playButton.txt", 1), COORD{150, 55}, UIButton::PLAY),
        ReturnMenu(new Animation("spriteAscii/button/MenuButton.txt", 1), COORD{156, 77}, UIButton::RETURN_MENU),
        ReplayLevel(new Animation("spriteAscii/button/ReplayButton.txt", 1), COORD{120, 77}, UIButton::REPLAY),
        NextLevel(new Animation("spriteAscii/button/NextButton.txt", 1), COORD{81, 77}, UIButton::NEXT),
        Dig_button(DIG_BUTTON, COORD{0, 84}),
        Umbrella_button(UMBRELLA_BUTTON, COORD{14, 84}),
        Wait_button(WAIT_BUTTON, COORD{28, 84}),
        Boom_button(BOOM_BUTTON, COORD{42, 84}),
        drop(new Animation("spriteAscii/drop/drop16.txt", 10), COORD{50, 20}, false),
        door(new Animation("spriteAscii/door/door16.txt", 6), COORD{145, 67}, true) // 145,67
    {
        initial_level = current_screen == LEVEL_ONE ? level_one : current_screen == LEVEL_TWO ? level_two : level_three;
        short borderMap = (short)initial_level.w_picture;
        minute = Element(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 22), 5}, false);
        sec1 = Element(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 15), 5}, false);
        sec2 = Element(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 10), 5}, false);
        _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8));
        _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8, true));
        _anims.push_back( new Animation("spriteAscii/lemming_fall/lem_fall_size8.txt", 4));
        _anims.push_back( new Animation("spriteAscii/lemming_dig/lem_dig_size10.txt", 16));
        _anims.push_back( new Animation("spriteAscii/lemming_end/lem_end10.txt", 8));
        _anims.push_back( new Animation("spriteAscii/boom/lem_boom_size10.txt", 12));
        _anims.push_back( new Animation("spriteAscii/crash/lem_crash.txt", 17));
        _anims.push_back( new Animation("spriteAscii/umbrella/lem_umbrella10.txt", 16));
        _anims.push_back( new Animation("spriteAscii/wait/lem_wait8.txt", 16));
        COORD centre_drop_lem{(short)(drop.get_center().X - _anims.at(2)->get_frame(0).w_picture/2), (short)(drop.get_center().Y - _anims.at(2)->get_frame(0).h_picture/2)};

        Lemming lem = Lemming(_anims, centre_drop_lem, FALL);
        lemmings.resize(10, Lemming(_anims, centre_drop_lem, FALL));        
    }
    
    static DrawLemming& Instance() {
        static DrawLemming S;
        return S;
    }
    ScreenEnum current_screen = LEVEL_THREE;
    ScreenEnum last_screen = MENU;
    TypeSkillButton currentSelectedSkill = NOTHING;

    int currentLevel;
    Picture title_screen;
    Picture initial_level;
    Picture level_one;
    Picture level_two;
    Picture level_three;
    Picture win_screen;
    Picture lose_screen;
    UIButton Quit;
    UIButton Play;
    UIButton ReturnMenu;
    UIButton ReplayLevel;
    UIButton NextLevel;
    vector<Lemming> lemmings;
    vector<Lemming> waiting_lemmings;
    vector<Animation*> _anims;
    
    SkillButton Dig_button;
    SkillButton Umbrella_button;
    SkillButton Wait_button;
    SkillButton Boom_button;
    Element drop;
    Element door;
    Element minute;
    Element sec1;
    Element sec2;
    void DrawPixel(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Hexa_color color);
    void DrawPicture(std::vector<std::vector<CHAR_INFO>> &buffer, int x, int y, Picture picture, bool debugOutline=false);
    void Refresh_win(std::vector<std::vector<CHAR_INFO>>& buffer);
    void Refresh_lose(std::vector<std::vector<CHAR_INFO>>& buffer);
    void Refresh_level(std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer& timer);
    void LoadLevel(int level);
    void resetSkillButtonState();
    void DisplayScreen(std::vector<std::vector<CHAR_INFO>>& buffer);
    void DrawLemmings(std::vector<std::vector<CHAR_INFO>>& buffer);

    bool isLevelEnded();
    void CheckIfLevelEnded();
};
