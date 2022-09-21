#include "Input.h"

Input::Input()
{
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );
    SetConsoleMode(hInput, fdwMode);
    FlushConsoleInputBuffer(hInput);
}

void Input::DrawMouse(std::vector<std::vector<CHAR_INFO>>& buffer, bool erase, bool onClick)
{
    if(onClick)
    {
        buffer[MousePos.Y][MousePos.X].Char.AsciiChar = erase ? ' ' : 'x';
        for(int x=-3; x <= 3;x++)
        {
            if(MousePos.X + x > 0 && MousePos.X + x < SCREEN_WIDTH)
            {
                if(MousePos.Y + 2 < SCREEN_HEIGHT)
                    buffer[MousePos.Y + 2][MousePos.X + x].Char.AsciiChar = erase ? ' ' : 'x';
                if(MousePos.Y - 2 > 0)
                    buffer[MousePos.Y - 2][MousePos.X + x].Char.AsciiChar = erase ? ' ' : 'x';
            }
        }
        for(int y=-1; y <= 1;y++)
        {
            if(MousePos.Y + y > 0 && MousePos.Y + y < SCREEN_HEIGHT)
            {
                if(MousePos.X + 3 < SCREEN_WIDTH)
                    buffer[MousePos.Y + y][MousePos.X + 3].Char.AsciiChar = erase ? ' ' : 'x';
                if(MousePos.X - 3 > 0)
                    buffer[MousePos.Y - y][MousePos.X - 3].Char.AsciiChar = erase ? ' ' : 'x';
            }
            
        }
    }
    else
    {
        for(int x=-3; x <= 3;x++)
            if(MousePos.X + x > 0 && MousePos.X + x < SCREEN_WIDTH)
                buffer[MousePos.Y][MousePos.X + x].Char.AsciiChar = erase ? ' ' : 'x';
        for(int y=-2; y <= 2;y++)
            if(MousePos.Y + y > 0 && MousePos.Y + y < SCREEN_HEIGHT)
                buffer[MousePos.Y + y][MousePos.X].Char.AsciiChar = erase ? ' ' : 'x';        
    }
}

bool onClick = false;
void Input::ProcessInput(std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer)
{
    DWORD nb;
    INPUT_RECORD record[200];
    
    buffer[5][5].Char.AsciiChar = 0x30 + static_cast<int>(timer.getElapsedSeconds());
    if (WaitForSingleObject(hInput, 50) == WAIT_OBJECT_0)
    {
        if (ReadConsoleInput(hInput,record,200,&nb))
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
