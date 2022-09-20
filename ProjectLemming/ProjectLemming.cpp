#define _WIN32_WINNT 0x0501
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#include <codecvt>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <fstream>

#include "NYTimer.h"

using namespace std;

HANDLE hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE );
HANDLE hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );
DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
COORD dwBufferCoord = { 0, 0 };
SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1 };

CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

LONG_PTR setConsoleWindowStyle(INT,LONG_PTR);

void setBackground(const char* str);
void setSimpleBackground(const char* str);

int main()
{
    NYTimer timer;
    timer.start();
    
    ReadConsoleOutput( hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion );
    buffer[5][10].Char.AsciiChar = 'H';
    buffer[5][10].Attributes = 0x0E;
    buffer[5][11].Char.AsciiChar = 'i';
    buffer[5][11].Attributes = 0x0B;
    buffer[5][12].Char.AsciiChar = '!';
    buffer[5][12].Attributes = 0x0A;
    LONG_PTR new_style =  WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
    setConsoleWindowStyle(GWL_STYLE,new_style);
    
    /*
    int res,type = MB_OK;
    res = MessageBox(NULL,_T("voila le message"),_T("voila le titre"),type);
    printf("Code de retour : %d\n",res);*/

    SetConsoleMode(hInput, fdwMode);
    DWORD nb;
    INPUT_RECORD record[200];
    
    //POINT pt;
    FlushConsoleInputBuffer(hInput);
    while(timer.getElapsedSeconds() <= 4)
    {
        buffer[5][5].Char.AsciiChar = 0x30 + static_cast<int>(timer.getElapsedSeconds());
        if (WaitForSingleObject(hInput, 100) == WAIT_OBJECT_0)
        {
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
        
        /* */
        if(static_cast<int>(timer.getElapsedSeconds()) % 2 == 0)
        {
            buffer[5][10].Attributes = 0x0E;
        } else 
            buffer[5][10].Attributes = 0x0B;
        WriteConsoleOutput( hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion );
        
    }

    return 0;
}

// void setBackground(const char* str)
// {
//     wifstream ansi_input{str};
//     ansi_input.open(str);
//
//     // Define the code page of the text file (1256 = Arabic)
//     ansi_input.imbue( std::locale( ".1256" ) );
//     // ansi_input.imbue( std::locale( ansi_input.getloc(), new std::codecvt_utf8_utf16< wchar_t, 1114111UL, std::consume_header> ) );
//     
//     // Read the whole file into a wstring.
//     // The stream converts from ANSI to UTF-16 encoding.
//     std::wstring ws{ std::istreambuf_iterator<wchar_t>( ansi_input ), std::istreambuf_iterator<wchar_t>() };
//     
//     if (ansi_input.is_open() == true)
//     {
//         wchar_t* psStr = &ws[0];
//         for (int i = 0; i < ws.size(); ++i)
//         {
//             wchar_t wc = psStr[i];
//             buffer[i/121][i%121].Char.AsciiChar = char(wc);
//             buffer[i/121][i%121].Attributes = wc;
//         }
//     }
//     
//     ansi_input.close();
//     
// }

void setSimpleBackground(const char* str)
{
    ifstream input;
    input.open(str);

    if (input.is_open() == true) {
        char c;
        int i = 0;
        while (input.get(c))
        {
            buffer[i/121][i%121].Char.AsciiChar = c;
            buffer[i/121][i%121].Attributes = 0x0E;
            i++;
        }
        input.close();
    }
}



//Si le new style est à 0, la fenetre n'a absolument rien à part son contenu
LONG_PTR setConsoleWindowStyle(INT n_index,LONG_PTR new_style)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);        

    HWND hwnd_console = GetConsoleWindow();
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console,n_index,new_style);
    SetWindowPos(hwnd_console,0,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_DRAWFRAME);

    //show window after updating
    ShowWindow(hwnd_console,SW_SHOW);

    return style_ptr;  
}