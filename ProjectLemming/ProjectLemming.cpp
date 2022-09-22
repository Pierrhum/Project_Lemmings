#define _WIN32_WINNT 0x0501


#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include "Animation.h"
#include "Input.h"
#include "NYTimer.h"
#include "DrawLemming.h"

using namespace std;

#include "WinConsole.h"

void setBackground(const char* str);
void setSimpleBackground(const char* str);

int main()
{
    NYTimer timer;
    Input input;
    timer.start();

    WinConsole Console;

    //ShowCursor(FALSE);
    ReadConsoleOutput( Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                        Console.dwBufferCoord, &Console.rcRegion );
    
    for(int y=0;y < Console.dwBufferSize.Y; y++)
        for(int x=0; x < Console.dwBufferSize.X;x++)
            Console.buffer[y][x].Attributes = 0x0F;

    Animation anim = Animation("spriteAscii/lem_mouve.txt", 8);
    int cpt = 0;
    while(1)
    {
        if(static_cast<int>(timer.getElapsedSeconds()) % 2 == 0)
        {
            
        }
        cpt++;
        DrawLemming::Instance().DrawPicture(Console.buffer, 0, 0, anim.get_frame(cpt%7));

        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        input.ProcessInput(Console.buffer, timer);        
    }
}