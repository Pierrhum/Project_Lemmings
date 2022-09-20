#include "Input.h"

Input::Input()
{
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );
    SetConsoleMode(hInput, fdwMode);
    FlushConsoleInputBuffer(hInput);
}

void Input::DrawMouse(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], bool erase)
{
    for(int x=-3; x <= 3;x++)
        if(MousePos.X + x > 0 && MousePos.X + x < SCREEN_WIDTH)
            buffer[MousePos.Y][MousePos.X + x].Char.AsciiChar = erase ? ' ' : 'x';
    for(int y=-2; y <= 2;y++)
        if(MousePos.Y + y > 0 && MousePos.Y + y < SCREEN_HEIGHT)
            buffer[MousePos.Y + y][MousePos.X].Char.AsciiChar = erase ? ' ' : 'x';
}

void Input::ProcessInput(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], NYTimer timer)
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
                    else DrawMouse(buffer, true);
                    
                    MousePos = record[i].Event.MouseEvent.dwMousePosition;
                    DrawMouse(buffer, false);
                    switch (record[i].Event.MouseEvent.dwButtonState)
                    {
                    case FROM_LEFT_1ST_BUTTON_PRESSED:
                        buffer[5][20].Char.AsciiChar = 'O';
                        break;
                    case RIGHTMOST_BUTTON_PRESSED:
                        buffer[5][20].Char.AsciiChar = 'U';
                        break;
                    case FROM_LEFT_2ND_BUTTON_PRESSED:
                        buffer[5][20].Char.AsciiChar = 'I';
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}
