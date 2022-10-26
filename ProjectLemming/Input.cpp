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
                        //for(Lemming lemming : lemmings)
                        //    if(lemming.is_showed && isOverlappingLemming(lemming))
                        //        lemming.current_state = DIG;
                        for (int lem = 0; lem < lemmings.size(); ++lem)
                            if (lemmings[lem].is_showed && isOverlapping(lemmings[lem], false) && lemmings[lem].current_state != FALL)
                                lemmings[lem].current_state = DIG;
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
                        break;
                    }
                }
            }
        }
    }
}