#include "Input.h"

#include "Lemming.h"

void Input::ProcessInput(vector<Lemming>& lemmings)
{
    DWORD nb;
    INPUT_RECORD record[200];

    // To avoid freezing the update method, we'll check the input every 50ms, instead of everytime
    if (WaitForSingleObject(Console.hInput, 50) == WAIT_OBJECT_0)
    {
        if (ReadConsoleInput(Console.hInput,record,200,&nb))
        {
            for(DWORD i=0;i<nb;i++)
            {
                if (record[i].EventType == MOUSE_EVENT)
                {
                    MousePos = record[i].Event.MouseEvent.dwMousePosition;
                    POS.X = MousePos.X - SIZE.X/2;
                    POS.Y = MousePos.Y * 2 - SIZE.Y / 2;

                            
                    switch (record[i].Event.MouseEvent.dwButtonState)
                    {
                    // Left click
                    case FROM_LEFT_1ST_BUTTON_PRESSED:
                        // If we click from the title screen
                        if(DrawLemming::Instance().current_screen == MENU)
                        {
                            ActionSkillLemming(lemmings);
                            if(isOverlapping(DrawLemming::Instance().Play, true))
                                DrawLemming::Instance().Play.onPress();
                            if(isOverlapping(DrawLemming::Instance().Quit, true))
                                DrawLemming::Instance().Quit.onPress();
                        }
                        // From the win menu
                        else if(DrawLemming::Instance().current_screen == WIN)
                        {
                            if(isOverlapping(DrawLemming::Instance().ReturnMenu, true))
                                DrawLemming::Instance().ReturnMenu.onPress();
                            if(isOverlapping(DrawLemming::Instance().ReplayLevel, true))
                                DrawLemming::Instance().ReplayLevel.onPress();
                            if(isOverlapping(DrawLemming::Instance().NextLevel, true))
                                DrawLemming::Instance().NextLevel.onPress();                            
                        }
                        // From the loose menu
                        else if(DrawLemming::Instance().current_screen == LOOSE)
                        {
                            if(isOverlapping(DrawLemming::Instance().ReturnMenu, true))
                                DrawLemming::Instance().ReturnMenu.onPress();
                            if(isOverlapping(DrawLemming::Instance().ReplayLevel, true))
                                DrawLemming::Instance().ReplayLevel.onPress();    
                        }
                        // From the other screens, ie the 3 levels
                        else
                        {
                            ActionSkillLemming(lemmings);
                            ActionSkillButton(DrawLemming::Instance().Dig_button);
                            ActionSkillButton(DrawLemming::Instance().Umbrella_button);
                            ActionSkillButton(DrawLemming::Instance().Wait_button);
                            ActionSkillButton(DrawLemming::Instance().Boom_button);                            
                        }
                        
                        mciSendString(TEXT("play sound/Click.wav"), NULL, 0, NULL);
                        mouseState = CLICK;
                        break;
                    // Every other state
                    default:
                        mouseState = NORMAL;
                        
                        // If the mouse overlaps a lemming
                        for (int lem = 0; lem < lemmings.size(); ++lem)
                            if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                                mouseState = HOVER;
                        
                        // If the mouse overlaps any button corresponding to the corresponding screen
                        if(DrawLemming::Instance().current_screen == MENU)
                        {
                            if(isOverlapping(DrawLemming::Instance().Play, true))
                                mouseState = HOVER;
                            if(isOverlapping(DrawLemming::Instance().Quit, true))
                                mouseState = HOVER;
                        }
                        else if(DrawLemming::Instance().current_screen == WIN)
                        {
                            if(isOverlapping(DrawLemming::Instance().ReturnMenu, true))
                                mouseState = HOVER;
                            if(isOverlapping(DrawLemming::Instance().ReplayLevel, true))
                                mouseState = HOVER;
                            if(isOverlapping(DrawLemming::Instance().NextLevel, true))
                                mouseState = HOVER;                            
                        }
                        else if(DrawLemming::Instance().current_screen == LOOSE)
                        {
                            if(isOverlapping(DrawLemming::Instance().ReturnMenu, true))
                                mouseState = HOVER;
                            if(isOverlapping(DrawLemming::Instance().ReplayLevel, true))
                                mouseState = HOVER;    
                        }
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
            // If we didn't select any button, a funny sound appears if we click on a Lemming
            case NOTHING:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                    mciSendString(TEXT("play sound/Ow.wav"), NULL, 0, NULL);
                break;
            // The Lemming has to be walking to apply Dig Skill
            case DIG_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false) &&
                        (lemmings[lem].current_state == LMOVE || lemmings[lem].current_state == RMOVE))
                        lemmings[lem].SetState(DIG);
                break;
            // The Lemming can receive the umbrella skill at any moment
            case UMBRELLA_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                    {
                        lemmings[lem].is_umbrellaed = true;
                        if (lemmings[lem].current_state == FALL)
                            lemmings[lem].SetState(UMBRELLA);
                    }
                break;
            // The Lemming has to be walking to apply Wait Skill, and we'll add it to the waiting_list, used in collisions checking
            case WAIT_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false)
                        && (lemmings[lem].current_state == LMOVE || lemmings[lem].current_state == RMOVE))
                    {
                        lemmings[lem].SetState(WAIT);
                        DrawLemming::Instance().waiting_lemmings.push_back(lemmings[lem]);
                    }
                break;
            // The Lemming can explode at any moment, we'll also remove it if it belongs to the waiting list, to remove the collision.
            case BOOM_BUTTON:
                for (int lem = 0; lem < lemmings.size(); ++lem)
                    if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false))
                    {
                        if(lemmings[lem].current_state == WAIT) DrawLemming::Instance().RemoveWaitingLemming(lemmings[lem]);
                        lemmings[lem].SetState(BOOM);
                    }
                break;
        }
}
