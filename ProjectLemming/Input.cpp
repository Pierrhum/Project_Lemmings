#include "Input.h"

#include "Lemming.h"

Hexa_color Input::GetHexaColor(Picture pic, int x, int y)
{
    return (Hexa_color)pic.get_pixel(MousePos.X + x, MousePos.Y * 2 + y);
}

void Input::ProcessInput(vector<Lemming>& lemmings, std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer)
{
    DWORD nb;
    INPUT_RECORD record[200];
    
    buffer[5][5].Char.AsciiChar = 0x30 + static_cast<int>(timer.getElapsedSeconds());
    if (WaitForSingleObject(Console.hInput, 50) == WAIT_OBJECT_0)
    {
        if (ReadConsoleInput(Console.hInput,record,200,&nb))
        {
            for(DWORD i=0;i<nb;i++)
            {
                if (record[i].EventType == MOUSE_EVENT)
                {
                    if(!MouseInit) MouseInit = true;
                    
                    MousePos = record[i].Event.MouseEvent.dwMousePosition;
                    POS.X = MousePos.X - SIZE.X/2;
                    POS.Y = MousePos.Y * 2 - SIZE.Y / 2;

                            
                    switch (record[i].Event.MouseEvent.dwButtonState)
                    {
                        // Clic gauche
                    case FROM_LEFT_1ST_BUTTON_PRESSED:
                        ActionSkillLemming(lemmings);
                        
                        if(isOverlapping(DrawLemming::Instance().Play, true))
                            DrawLemming::Instance().Play.onPress();
                        if(isOverlapping(DrawLemming::Instance().ReturnMenu, false))
                            DrawLemming::Instance().ReturnMenu.onPress();
                        if(isOverlapping(DrawLemming::Instance().ReplayLevel, true))
                            DrawLemming::Instance().ReplayLevel.onPress();
                        if(isOverlapping(DrawLemming::Instance().NextLevel, true))
                            DrawLemming::Instance().NextLevel.onPress();
                        
                        ActionSkillButton(DrawLemming::Instance().Dig_button);
                        ActionSkillButton(DrawLemming::Instance().Umbrella_button);
                        ActionSkillButton(DrawLemming::Instance().Wait_button);
                        ActionSkillButton(DrawLemming::Instance().Boom_button);
                        mouseState = CLICK;
                        break;
                        // Clic droit
                    case RIGHTMOST_BUTTON_PRESSED:
                        mouseState = CLICK;
                        break;
                        // Clic molette
                    case FROM_LEFT_2ND_BUTTON_PRESSED:
                        mouseState = CLICK;
                        break;
                        // Aucun clic : affichge de la souris
                    default:
                        mouseState = NORMAL;
                        for (int lem = 0; lem < lemmings.size(); ++lem)
                            if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                                mouseState = HOVER;
                        if(isOverlapping(DrawLemming::Instance().Play, true))
                            mouseState = HOVER;
                        break;
                    }
                }
            }
        }
    }
}

void Input::ActionSkillButton(SkillButton& skill_button)
{
    if (isOverlapping(skill_button, true))
    {
        if (DrawLemming::Instance().currentSelectedSkill != NOTHING &&
            DrawLemming::Instance().currentSelectedSkill != skill_button.type_button)  
                DrawLemming::Instance().resetSkillButtonState();
        skill_button.onPress();
    }
}

void Input::ActionSkillLemming(vector<Lemming>& lemmings)
{
        switch (DrawLemming::Instance().currentSelectedSkill)
        {
            case NOTHING:
                break;
            case DIG_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false) &&
                        (lemmings[lem].current_state == LMOVE || lemmings[lem].current_state == RMOVE))
                        lemmings[lem].current_state = DIG;
                break;
            case UMBRELLA_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                    {
                        lemmings[lem].is_umbrellaed = true;
                        if (lemmings[lem].current_state == FALL)
                            lemmings[lem].current_state = UMBRELLA;
                    }
                break;
            case WAIT_BUTTON:
                break;
            case BOOM_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                {
                    lemmings[lem].current_state = BOOM;
                }
                break;
        }
}
