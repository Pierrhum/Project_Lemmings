#include "Input.h"

Hexa_color Input::GetHexaColor(Picture pic, int x, int y)
{
    return (Hexa_color)pic.get_pixel(MousePos.X + x, MousePos.Y * 2 + y);
}

void Input::DrawMouse(std::vector<std::vector<CHAR_INFO>>& buffer, bool erase, bool onClick)
{

    if(MousePos.Y > Console.dwBufferSize.Y - 10) return;
    if(MousePos.X > Console.dwBufferSize.X - 35) return;
    
    Picture pic = DrawLemming::Instance().intial_level;
    if(onClick)
    {
        DrawLemming::Instance().DrawPixel(buffer, MousePos.X, MousePos.Y * 2, erase ? GetHexaColor(pic, 0,0) : RED);
        for(int x=-3; x <= 3;x++)
        {
            if(MousePos.X + x > 0 && MousePos.X + x < Console.dwBufferSize.X)
            {
                if(MousePos.Y + 2 < Console.dwBufferSize.Y)
                    DrawLemming::Instance().DrawPixel(buffer, MousePos.X + x, MousePos.Y * 2 + 2, erase ? GetHexaColor(pic, x,2) : PURPLE);
                if(MousePos.Y - 2 > 0)
                    DrawLemming::Instance().DrawPixel(buffer, MousePos.X + x, MousePos.Y * 2 - 2, erase ? GetHexaColor(pic, x,-2) : PURPLE);
            }
        }
        for(int y=-1; y <= 1;y++)
        {
            if(MousePos.Y + y > 0 && MousePos.Y + y < Console.dwBufferSize.Y)
            {
                if(MousePos.X + 3 < Console.dwBufferSize.X)
                    DrawLemming::Instance().DrawPixel(buffer, MousePos.X + 3, MousePos.Y * 2 + y, erase ? GetHexaColor(pic, 3,y) : PURPLE);
                if(MousePos.X - 3 > 0)
                    DrawLemming::Instance().DrawPixel(buffer, MousePos.X - 3, MousePos.Y * 2 + y, erase ? GetHexaColor(pic, -3,y) : PURPLE);
            }
            
        }
    }
    else
    {
        for(int x=-3; x <= 3;x++)
            if(MousePos.X + x > 0 && MousePos.X + x < Console.dwBufferSize.X)
                DrawLemming::Instance().DrawPixel(buffer, MousePos.X + x, MousePos.Y * 2, erase ? GetHexaColor(pic, x,0) : PURPLE);
        for(int y=-2; y <= 2;y++)
            if(MousePos.Y + y > 0 && MousePos.Y + y < Console.dwBufferSize.Y)
                DrawLemming::Instance().DrawPixel(buffer, MousePos.X, MousePos.Y * 2 + y , erase ? GetHexaColor(pic, 0,y) : PURPLE);
    }
}

bool onClick = false;
void Input::ProcessInput(std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer)
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
                    else DrawMouse(buffer, true, onClick);
                    
                    MousePos = record[i].Event.MouseEvent.dwMousePosition;
                    switch (record[i].Event.MouseEvent.dwButtonState)
                    {
                    case FROM_LEFT_1ST_BUTTON_PRESSED:
                        buffer[5][20].Char.AsciiChar = 'O';
                        DrawMouse(buffer, false, (onClick=true));
                        break;
                    case RIGHTMOST_BUTTON_PRESSED:
                        buffer[5][20].Char.AsciiChar = 'U';
                        break;
                    case FROM_LEFT_2ND_BUTTON_PRESSED:
                        buffer[5][20].Char.AsciiChar = 'I';
                        break;
                    default:
                        DrawMouse(buffer, false, false);
                        onClick=false;
                        break;
                    }
                }
            }
        }
    }
}
