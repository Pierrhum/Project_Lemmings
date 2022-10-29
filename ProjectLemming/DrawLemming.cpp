#include "DrawLemming.h"

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

void DrawLemming::Refresh_win(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawPicture(buffer, 0, 0, win_screen);
    ReturnMenu.POS = {156, 77};
    ReturnMenu.play_frame(buffer, 0);  
    ReplayLevel.POS = {120, 77};
    ReplayLevel.play_frame(buffer, 0);  
    NextLevel.play_frame(buffer, 0);  
}

void DrawLemming::Refresh_lose(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawPicture(buffer, 0, 0, lose_screen);
    ReturnMenu.POS = {117,73};
    ReturnMenu.play_frame(buffer, 0);
    ReplayLevel.POS = {41,74};
    ReplayLevel.play_frame(buffer, 0);  
}

void DrawLemming::Refresh_level(std::vector<std::vector<CHAR_INFO>> &buffer, NYTimer& timer)
{
    DrawPicture(buffer, 0, 0, initial_level);

    drop.play_next_frame(buffer);
    door.play_next_frame(buffer);
    //draw HUB
    Dig_button.play_frame(buffer, 0);  
    Umbrella_button.play_frame(buffer, 0);  
    Wait_button.play_frame(buffer, 0);  
    Boom_button.play_frame(buffer, 0);
    
    // Gestion du timer
    int _minute = timer.getRemainingTime() / 60;
    int _seconde = timer.getRemainingTime() - (_minute * 60);
    // Affichage
    minute.play_frame(buffer, _minute);
    DrawPixel(buffer, minute.POS.X + minute.SIZE.X + 1, minute.POS.Y + 2, WHITE);
    DrawPixel(buffer, minute.POS.X + minute.SIZE.X + 1, minute.POS.Y + 4, WHITE);
    sec1.play_frame(buffer, _seconde / 10);
    sec2.play_frame(buffer, _seconde % 10);
}

void DrawLemming::LoadLevel(int level)
{
    last_screen = current_screen;
    
    State defaultLemmingState = FALL;
    int nbLemming = 1;
    
    switch (level)
    {
        case 0:
            current_screen = MENU;
            initial_level = title_screen;
            drop.POS = {0, 50};
            currentSelectedSkill = BOOM_BUTTON;
            defaultLemmingState = RMOVE;
            nbLemming = 10;
            PlaySound(TEXT("sound/menu.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;
        case 1:
            currentLevel = current_screen = LEVEL_ONE;
            initial_level = level_one;
            drop.next_frame_to_play = 0;
            drop.POS = {50, 20};
            door.POS = {60, 30}; // 145 67
            currentSelectedSkill = NOTHING;
            nbLemming = 2;
            nbLemmingToWin = 1;
            PlaySound(TEXT("sound/level1.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;
        case 2:
            currentLevel = current_screen = LEVEL_TWO;
            initial_level = level_two;
            drop.next_frame_to_play = 0;
            drop.POS = {2, 2};
            door.POS = {160, 78};
            currentSelectedSkill = NOTHING;
            nbLemming = 10;
            nbLemmingToWin = 8;
            PlaySound(TEXT("sound/level2.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;
        case 3:
            currentLevel = current_screen = LEVEL_THREE;
            initial_level = level_three;
            drop.next_frame_to_play = 0;
            drop.POS = {77, 0};
            door.POS = {60, 81};
            currentSelectedSkill = NOTHING;
            nbLemming = 20;
            nbLemmingToWin = 15;
            PlaySound(TEXT("sound/level3.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;

        case 4:
            current_screen = WIN;
            initial_level = win_screen;
            nbLemming = 0;
            PlaySound(TEXT("sound/win.wav"), NULL, SND_ASYNC);
            break;
            
        case 5:
            current_screen = LOOSE;
            initial_level = lose_screen;
            nbLemming = 0;
            PlaySound(TEXT("sound/loose.wav"), NULL, SND_ASYNC);
            break;
        
        default:
            break;
    }
    
    lemmings.clear();
    waiting_lemmings.clear();
    COORD centre_drop_lem = {(short)(drop.get_center().X - _anims.at(defaultLemmingState)->get_frame(0).w_picture/2), (short)(drop.get_center().Y - _anims.at(defaultLemmingState)->get_frame(0).h_picture/2)};
    lemmings.resize(nbLemming, Lemming(_anims, centre_drop_lem, defaultLemmingState));        

}

void DrawLemming::resetSkillButtonState()
{
    Dig_button.resetEtat();
    Umbrella_button.resetEtat();
    Wait_button.resetEtat();
    Boom_button.resetEtat();
}

void DrawLemming::DisplayScreen(std::vector<std::vector<CHAR_INFO>>& buffer)
{
    DrawPicture(buffer, 0, 0, title_screen);
    Play.play_frame(buffer, 0);  
    Quit.play_frame(buffer, 0);  
}

void DrawLemming::DrawLemmings(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).is_showed)
        {
            if(lemmings.at(i).current_state != END && lemmings.at(i).isOverlapping(door, true)) lemmings.at(i).SetState(END);
            lemmings.at(i).Update(buffer);
        }
    
}

bool DrawLemming::isLevelEnded()
{
    bool ended = true;
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).current_state != END) ended = false;

    return ended;
}

void DrawLemming::CheckIfLevelEnded()
{
    int winAmount = 0;
    bool ended = true;
    
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).current_state == END) winAmount++; // WIN
        else if(lemmings.at(i).current_state != DEAD) ended = false;

    if(ended)
    {
        if(winAmount >= nbLemmingToWin) LoadLevel(WIN);
        else LoadLevel(LOOSE);
    }
}
