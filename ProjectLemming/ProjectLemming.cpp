#define _WIN32_WINNT 0x0501


#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include "Input.h"
#include "NYTimer.h"
#include "DrawLemming.h"
#include "GlobalObjects.h"

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
    
    GlobalObjects::Instance().InitLevelOne();
    
    int last_second = 0;
    int timing_frame = 100;
    while(1)
    {
        if(static_cast<int>(timer.getElapsedMs()/timing_frame) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedMs()/timing_frame);
            DrawLemming::Instance().Refresh_init_level(Console.buffer);
            GlobalObjects::Instance().drop.play_next_frame(Console.buffer);
            GlobalObjects::Instance().door.play_next_frame(Console.buffer);

            if (GlobalObjects::Instance().drop.end_anim) GlobalObjects::Instance().lemming.at(0).play_next_frame(Console.buffer);
        }
        
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        input.ProcessInput(Console.buffer, timer);        
    }
}