#include "Input.h"

Input::Input()
{
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );
    SetConsoleMode(hInput, fdwMode);
    FlushConsoleInputBuffer(hInput);
}

void Input::ProcessInput(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], NYTimer timer)
{
    DWORD nb;
    INPUT_RECORD record[200];
    
    POINT pt;
        buffer[5][5].Char.AsciiChar = 0x30 + static_cast<int>(timer.getElapsedSeconds());
        if (WaitForSingleObject(hInput, 100) == WAIT_OBJECT_0)
        {
            GetCursorPos(&pt);
            buffer[pt.y][pt.x].Char.AsciiChar = 'x';
            if (ReadConsoleInput(hInput,record,200,&nb))
            {
                for(DWORD i=0;i<nb;i++)
                {
                    if (record[i].EventType == MOUSE_EVENT)
                    {
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
