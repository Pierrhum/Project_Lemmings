#define _WIN32_WINNT 0x0501


#include <iostream>
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
    NYTimer timer(10);
    timer.start();

    //ShowCursor(FALSE);
    ReadConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                      Console.dwBufferCoord, &Console.rcRegion);
    
    int last_second = 0;
    int timing_frame = 100;
    int lapse_spawn = 3;
    int spawn_counter = 0;
    int next_lemming = 0;
    bool title_screen = true;
    while (1)
    {
        if(title_screen)
        {
            DrawLemming::Instance().DisplayScreen(Console.buffer);
            input.play_frame(Console.buffer, input.onClick);
        }
        else
        {
            if (static_cast<int>(timer.getElapsedMs() / timing_frame) > last_second)
            {
                last_second = static_cast<int>(timer.getElapsedMs() / timing_frame);
                DrawLemming::Instance().Refresh_level(Console.buffer);

                DrawLemming::Instance().DrawLemmings(Console.buffer, timer);
            
                if(timer.getRemainingTime() == 0)
                    MessageBox(NULL,_T("Looser!"),_T("Lemmings"),MB_OK);
                else if(DrawLemming::Instance().isLevelEnded())
                    MessageBox(NULL,_T("Victory!"),_T("Lemmings"),MB_OK);
            
                else if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&
                    spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                    next_lemming<DrawLemming::Instance().lemmings.size())
                {
                    DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                    next_lemming++;
                }
                spawn_counter = static_cast<int>(timer.getElapsedMs() / 1000);
                input.play_frame(Console.buffer, input.onClick);
            }
        }
        

        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord,
                           &Console.rcRegion);
        input.ProcessInput(DrawLemming::Instance().lemmings, Console.buffer, timer);

    }        
}
