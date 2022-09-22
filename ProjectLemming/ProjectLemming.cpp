#define _WIN32_WINNT 0x0501


#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include "Input.h"
#include "NYTimer.h"
#include "DrawLemming.h"

using namespace std;

#include "WinConsole.h"

void setBackground(const char* str);
void setSimpleBackground(const char* str);

int main()
{
    WinConsole Console;
    Input input(Console);
    NYTimer timer;
    timer.start();

    //ShowCursor(FALSE);
    ReadConsoleOutput( Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                        Console.dwBufferCoord, &Console.rcRegion );
    
    Picture picture("spriteAscii/backgroundTest200_100.txt");
    DrawLemming::Instance().intial_level = picture;
    DrawLemming::Instance().DrawPicture(Console.buffer, 0, 0, picture);

    while(1)
    {
        if(static_cast<int>(timer.getElapsedSeconds()) % 2 == 0)
        {
            Console.buffer[5][10].Attributes = 0x0E;
        } else 
            Console.buffer[5][10].Attributes = 0x0B;

        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        input.ProcessInput(Console.buffer, timer);        
    }
}