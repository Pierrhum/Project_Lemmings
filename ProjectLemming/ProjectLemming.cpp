#define _WIN32_WINNT 0x0501
#pragma comment(lib, "winmm.lib")

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

enum ScreenEnum
{
    MENU,
    WIN,
    LOOSE,
    LEVEL_ONE
};

int main()
{
    WinConsole Console;
    Input input(Console);
    NYTimer timer(10);

    //ShowCursor(FALSE);
    ReadConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                      Console.dwBufferCoord, &Console.rcRegion);

    ScreenEnum current_screen = LEVEL_ONE;
    ScreenEnum last_screen = MENU;
    
    //https://learn.microsoft.com/en-us/previous-versions/dd743680(v=vs.85)
    //https://learn.microsoft.com/fr-fr/windows/win32/multimedia/using-playsound-to-loop-sounds
    PlaySound(TEXT("sound/Lemmings_JustDig.wav"), NULL, SND_LOOP | SND_ASYNC);
    //PlaySound(NULL, NULL, 0); //stop sound

    //Element testanim(new Animation("spriteAscii/crash/lem_crash.txt", 17), COORD{0,0}, true);
    
    //Element testanim(new Animation("spriteAscii/umbrella/lem_umbrella10.txt", 16), COORD{0,0}, true);
    ////testanim.play_next_frame(Console.buffer, {0,0}, 4);

    
    
    int last_second = 0;
    int timing_frame = 100;
    int lapse_spawn = 3, spawn_counter = 0, next_lemming = 0;
    while (1)
    {
        if (static_cast<int>(timer.getElapsedMs() / timing_frame) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedMs() / timing_frame);
            if (current_screen == MENU)
            {
                DrawLemming::Instance().DisplayScreen(Console.buffer);
                input.play_frame(Console.buffer, input.mouseState);
            }
            else if (current_screen == WIN)
            {
                DrawLemming::Instance().Refresh_win(Console.buffer);
                input.play_frame(Console.buffer, input.mouseState);
            }
            else if (current_screen == LOOSE)
            {
                DrawLemming::Instance().Refresh_lose(Console.buffer);
                input.play_frame(Console.buffer, input.mouseState);
            }
            else if (current_screen == LEVEL_ONE)
            {
                if (last_screen != current_screen)
                {
                    timer.start();
                    lapse_spawn = 3;
                    spawn_counter = 0;
                    next_lemming = 0;
                }
                DrawLemming::Instance().Refresh_level(Console.buffer);                
                // testanim.play_next_frame(Console.buffer);
                
                DrawLemming::Instance().DrawLemmings(Console.buffer, timer);
                if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&    
                    spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                    next_lemming<DrawLemming::Instance().lemmings.size())
                {
                    DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                    next_lemming++;
                }
                //if(timer.getRemainingTime() == 0)
                //    MessageBox(NULL,_T("Looser!"),_T("Lemmings"),MB_OK);
                //else if(DrawLemming::Instance().isLevelEnded())
                //    MessageBox(NULL,_T("Victory!"),_T("Lemmings"),MB_OK);
            }
            last_screen = current_screen;
            spawn_counter = static_cast<int>(timer.getElapsedMs() / 1000);
            input.play_frame(Console.buffer, input.mouseState);
        }
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord,
                           &Console.rcRegion);
        input.ProcessInput(DrawLemming::Instance().lemmings, Console.buffer, timer);
    }        
}
