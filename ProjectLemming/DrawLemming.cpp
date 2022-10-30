#include "DrawLemming.h"

/**
 * \brief Used to destroy lemmings you have click on when this lemmings is in waiting mode.
 * \param Lemming Lemmings you have click on
 */
void DrawLemming::RemoveWaitingLemming(Lemming& Lemming)
{
    int index = -1;

    for (int i = 0; i < waiting_lemmings.size(); ++i)
        if (waiting_lemmings.at(i).current_state == WAIT
            && waiting_lemmings.at(i).POS.X == Lemming.POS.X
            && waiting_lemmings.at(i).POS.Y == Lemming.POS.Y)
                index = i;
        
    if(index != -1)
        waiting_lemmings.erase(waiting_lemmings.begin() + index);
}

/**
 * \brief Draw pixel methode
 * \param buffer Console screen buffer
 * \param x Draw pixel position X axis
 * \param y Draw pixel position Y axis
 * \param color Color pixel you want
 */
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

/**
 * \brief Draw picture methode
 * \param buffer Console screen buffer
 * \param x Draw picture position X axis
 * \param y Draw picture position Y axis
 * \param picture Picture you want to show
 * \param debugOutline Show border of picture to debug (used to debug lemming physics collider pixels)
 */
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

/**
 * \brief Used in main loop to refresh title screen and reset elements his data
 * \param buffer Console screen buffer
 */
void DrawLemming::Refresh_menu(std::vector<std::vector<CHAR_INFO>>& buffer)
{
    DrawPicture(buffer, 0, 0, title_screen);
    Play.play_frame(buffer, 0);  
    Quit.play_frame(buffer, 0);  
}

/**
 * \brief Used in main loop to refresh win screen and reset elements his data
 * \param buffer Console screen buffer
 */
void DrawLemming::Refresh_win(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawPicture(buffer, 0, 0, win_screen);
    ReturnMenu.POS = {156, 77};
    ReturnMenu.play_frame(buffer, 0);  
    ReplayLevel.POS = {120, 77};
    ReplayLevel.play_frame(buffer, 0);  
    NextLevel.play_frame(buffer, 0);  
}

/**
 * \brief Used in main loop to refresh lose screen and reset elements his data
 * \param buffer Console screen buffer
 */
void DrawLemming::Refresh_lose(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawPicture(buffer, 0, 0, lose_screen);
    ReturnMenu.POS = {117,73};
    ReturnMenu.play_frame(buffer, 0);
    ReplayLevel.POS = {41,74};
    ReplayLevel.play_frame(buffer, 0);  
}

bool once = true;

/**
 * \brief Used in main loop to refresh current level screen and reset elements his data
 * \param buffer Console screen buffer
 * \param timer  Console timer
 */
void DrawLemming::Refresh_level(std::vector<std::vector<CHAR_INFO>> &buffer, NYTimer& timer)
{
    DrawPicture(buffer, 0, 0, current_scene);

    drop.play_next_frame(buffer);
    door.play_next_frame(buffer);

    if(once && door.next_frame_to_play==door.animations[0]->nb_frames-1)
    {
        once = false;
        mciSendString(TEXT("play sound/LetsGo.wav"), NULL, 0, NULL);
    }
    //draw HUB
    Dig_button.play_frame(buffer, 0);  
    Umbrella_button.play_frame(buffer, 0);  
    Wait_button.play_frame(buffer, 0);  
    Boom_button.play_frame(buffer, 0);
    
    // Timer management
    int _minute = timer.getRemainingTime() / 60;
    int _seconde = timer.getRemainingTime() - (_minute * 60);
    // Display
    minute.play_frame(buffer, _minute);
    DrawPixel(buffer, minute.POS.X + minute.SIZE.X + 1, minute.POS.Y + 2, WHITE);
    DrawPixel(buffer, minute.POS.X + minute.SIZE.X + 1, minute.POS.Y + 4, WHITE);
    sec1.play_frame(buffer, _seconde / 10);
    sec2.play_frame(buffer, _seconde % 10);
}

/**
 * \brief Reinit data for the screen scene "level" you want to load
 * \param level Number of level you load
 */
void DrawLemming::LoadScene(int level)
{
    last_screen = current_screen;
    
    State defaultLemmingState = FALL;
    int nbLemming = 1;
    
    switch (level)
    {
        case 0:
            current_screen = MENU;
            current_scene = title_screen;
            drop.POS = {-10, 50};
            currentSelectedSkill = BOOM_BUTTON;
            defaultLemmingState = RMOVE;
            nbLemming = 500;
            PlaySound(TEXT("sound/menu.wav"), NULL, SND_LOOP | SND_ASYNC);
            break;
        case 1:
            currentLevel = current_screen = LEVEL_ONE;
            current_scene = level_one;
            drop.next_frame_to_play = 0;
            drop.POS = {50, 20};
            door.POS = {145, 67}; // 145 67
            resetSkillButtonState();
            currentSelectedSkill = NOTHING;
            nbLemming = 10;
            nbLemmingToWin = 7;
            once = true;
            PlaySound(TEXT("sound/level1.wav"), NULL, SND_LOOP | SND_ASYNC);
            mciSendString(TEXT("play sound/DoorOpen.wav"), NULL, 0, NULL);
            break;
        case 2:
            currentLevel = current_screen = LEVEL_TWO;
            current_scene = level_two;
            drop.next_frame_to_play = 0;
            drop.POS = {2, 2};
            door.POS = {160, 78};
            resetSkillButtonState();
            currentSelectedSkill = NOTHING;
            nbLemming = 7;
            nbLemmingToWin = 5;
            once = true;
            PlaySound(TEXT("sound/level2.wav"), NULL, SND_LOOP | SND_ASYNC);
            mciSendString(TEXT("play sound/DoorOpen.wav"), NULL, 0, NULL);
            break;
        case 3:
            currentLevel = current_screen = LEVEL_THREE;
            current_scene = level_three;
            drop.next_frame_to_play = 0;
            drop.POS = {77, 0};
            door.POS = {60, 81};
            resetSkillButtonState();
            currentSelectedSkill = NOTHING;
            nbLemming = 20;
            nbLemmingToWin = 14;
            once = true;
            PlaySound(TEXT("sound/level3.wav"), NULL, SND_LOOP | SND_ASYNC);
            mciSendString(TEXT("play sound/DoorOpen.wav"), NULL, 0, NULL);
            break;

        case 4:
            current_screen = WIN;
            current_scene = win_screen;
            nbLemming = 0;
            PlaySound(TEXT("sound/win.wav"), NULL, SND_ASYNC);
            break;
            
        case 5:
            current_screen = LOOSE;
            current_scene = lose_screen;
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

/**
 * \brief Look at All SkillButton to reset their statement to not active
 */
void DrawLemming::resetSkillButtonState()
{
    Dig_button.resetEtat();
    Umbrella_button.resetEtat();
    Wait_button.resetEtat();
    Boom_button.resetEtat();
}

/**
 * \brief Show lemmings list in all level and check is lemmings is noticeable 
 * \param buffer Console screen buffer
 */
void DrawLemming::DrawLemmings(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).is_showed)
        {
            if(lemmings.at(i).current_state != END && lemmings.at(i).isOverlapping(door, true)) lemmings.at(i).SetState(END);
            else if(!lemmings.empty()) lemmings.at(i).Update(buffer);
        }
}

/**
 * \brief check in levels (one, two or three) if the game is lose or win
 */
void DrawLemming::CheckIfLevelEnded()
{
    int winAmount = 0;
    bool ended = true;
    
    for (int i = 0; i < lemmings.size(); ++i)
        if (lemmings.at(i).current_state == END) winAmount++; // WIN
        else if(lemmings.at(i).current_state != DEAD && lemmings.at(i).current_state != WAIT) ended = false;

    if(ended)
    {
        if(winAmount >= nbLemmingToWin) LoadScene(WIN);
        else LoadScene(LOOSE);
    }
}
