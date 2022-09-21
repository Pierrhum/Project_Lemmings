#define _WIN32_WINNT 0x0501

#include <stdio.h>
#include <iostream>
#include <numeric>
#include <windows.h>
#include <tchar.h>
#include <vector>

#include "Input.h"
#include "NYTimer.h"

HANDLE hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE );

COORD dwBufferSize ;
COORD dwBufferCoord = { 0, 0 };
SMALL_RECT rcRegion;

//CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

std::vector<std::vector<CHAR_INFO>> buffer;

LONG_PTR setConsoleWindowStyle(INT,LONG_PTR);

int main()
{
    NYTimer timer;
    Input input;
    timer.start();
    std::vector<CHAR_INFO> flat_vect;

    CONSOLE_SCREEN_BUFFER_INFO info;
    if(GetConsoleScreenBufferInfo(hOutput, &info)) {
        COORD coord;
        coord.X = 213;
        coord.Y = 45;
        dwBufferSize = { coord.X,coord.Y };
        rcRegion = { 0, 0, coord.X-1, coord.Y-1 };
        buffer.resize(coord.Y, std::vector<CHAR_INFO>(coord.X));

        buffer[0][0].Char.AsciiChar = '!';
        buffer[coord.Y/2][coord.X/2].Char.AsciiChar = '!';

        flat_vect =
            std::accumulate(buffer.begin(), buffer.end(),
                            std::vector<CHAR_INFO>(),
                            [](std::vector<CHAR_INFO>& a, std::vector<CHAR_INFO>& b) {
                                a.insert(a.end(), b.begin(), b.end());
                                return a;
                            });
        
        SetConsoleScreenBufferSize(hOutput, coord);
    }
    
    //ShowCursor(FALSE);
    ReadConsoleOutput( hOutput, flat_vect.data(), dwBufferSize, dwBufferCoord, &rcRegion );
    for(int y=0;y < dwBufferSize.Y; y++)
        for(int x=0; x < dwBufferSize.X;x++)
            buffer[y][x].Attributes = 0x0F;
    
    buffer[5][10].Char.AsciiChar = 'H';
    buffer[5][10].Attributes = 0x0E;
    buffer[5][11].Char.AsciiChar = 'i';
    buffer[5][11].Attributes = 0x0B;
    buffer[5][12].Char.AsciiChar = '!';
    buffer[5][12].Attributes = 0x0A;
    for(int y=0;y < dwBufferSize.Y; y++)
    {
        buffer[y][0].Char.AsciiChar = '|';
        buffer[y][0].Attributes = 0x0A;
        buffer[y][dwBufferSize.X-1].Char.AsciiChar = '|';
        buffer[y][dwBufferSize.X-1].Attributes = 0x0A;
    }
    
    for(int x=0; x < dwBufferSize.X;x++)
    {
        buffer[0][x].Char.AsciiChar = '-';
        buffer[0][x].Attributes = 0x0A;
        buffer[dwBufferSize.Y-1][x].Char.AsciiChar = '-';
        buffer[dwBufferSize.Y-1][x].Attributes = 0x0A;
    }
    LONG_PTR new_style =  WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
    setConsoleWindowStyle(GWL_STYLE,new_style);

    //MessageBox(NULL,_T("voila le message"),_T("voila le titre"),MB_OK);


    while(1)
    {
        if(static_cast<int>(timer.getElapsedSeconds()) % 2 == 0)
        {
            buffer[5][10].Attributes = 0x0E;
        } else 
            buffer[5][10].Attributes = 0x0B;
        flat_vect =
            std::accumulate(buffer.begin(), buffer.end(),
                            std::vector<CHAR_INFO>(),
                            [](std::vector<CHAR_INFO>& a, std::vector<CHAR_INFO>& b) {
                                a.insert(a.end(), b.begin(), b.end());
                                return a;
                            });
        WriteConsoleOutput( hOutput, flat_vect.data(), dwBufferSize, dwBufferCoord, &rcRegion );
        
        input.ProcessInput(buffer, timer);        
    }

    return 0;
}

//Si le new style est à 0, la fenetre n'a absolument rien à part son contenu
LONG_PTR setConsoleWindowStyle(INT n_index,LONG_PTR new_style)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);        

    HWND hwnd_console = GetConsoleWindow();
    SetConsoleTitleA("The Lemmings");
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console,n_index,new_style);
    SetConsoleWindowInfo(hwnd_console, 1, &rcRegion);

    
   // SetWindowPos(hwnd_console,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SWP_NOMOVE|SWP_DRAWFRAME);

    //show window after updating
    ShowWindow(hwnd_console,SW_MAXIMIZE);

    return style_ptr;  
}