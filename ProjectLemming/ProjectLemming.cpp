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

    Animation anim = Animation("spriteAscii/lem_mouve.txt", 8);
    int cpt = 0;
    int last_second = 0;
    while(1)
    {
        if(static_cast<int>(timer.getElapsedSeconds()) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedSeconds());
            DrawLemming::Instance().DrawPicture(Console.buffer, 0, 0, anim.get_frame(cpt++%7));
        }
        
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        input.ProcessInput(Console.buffer, timer);        
    }
}