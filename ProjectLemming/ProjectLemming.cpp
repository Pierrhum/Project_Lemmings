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


int main()
{
    WinConsole Console;
    Input input(Console);
    NYTimer timer(10);

    //ShowCursor(FALSE);
    ReadConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                      Console.dwBufferCoord, &Console.rcRegion);
    
    //https://learn.microsoft.com/en-us/previous-versions/dd743680(v=vs.85)
    //https://learn.microsoft.com/fr-fr/windows/win32/multimedia/using-playsound-to-loop-sounds
    PlaySound(TEXT("sound/menu.wav"), NULL, SND_LOOP | SND_ASYNC);
    //PlaySound(NULL, NULL, 0); //stop sound
    
    int last_second = 0;
    int timing_frame = 100;
    int lapse_spawn = 3, spawn_counter = 0, next_lemming = 0;
    
    DrawLemming::Instance().LoadLevel(MENU);
    
    while (1)
    {
        if (static_cast<int>(timer.getElapsedMs() / timing_frame) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedMs() / timing_frame);
            if (DrawLemming::Instance().current_screen == MENU)
            {
                DrawLemming::Instance().DisplayScreen(Console.buffer);
                
                DrawLemming::Instance().DrawLemmings(Console.buffer, timer);
                if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&    
                    spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                    next_lemming<DrawLemming::Instance().lemmings.size())
                {
                    DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                    next_lemming++;
                }
                input.play_frame(Console.buffer, input.mouseState);
            }
            else if (DrawLemming::Instance().current_screen == WIN)
            {
                DrawLemming::Instance().Refresh_win(Console.buffer);
                input.play_frame(Console.buffer, input.mouseState);
            }
            else if (DrawLemming::Instance().current_screen == LOOSE)
            {
                DrawLemming::Instance().Refresh_lose(Console.buffer);
                input.play_frame(Console.buffer, input.mouseState);
            }
            else if (DrawLemming::Instance().current_screen == LEVEL_ONE)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    timer = NYTimer(20);
                    timer.start();
                    lapse_spawn = 3;
                    spawn_counter = 0;
                    next_lemming = 0;
                }
                DrawLemming::Instance().Refresh_level(Console.buffer);          
                
                DrawLemming::Instance().DrawLemmings(Console.buffer, timer);
                if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&    
                    spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                    next_lemming<DrawLemming::Instance().lemmings.size())
                {
                    DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                    next_lemming++;
                }
            }
            else if (DrawLemming::Instance().current_screen == LEVEL_TWO)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    timer = NYTimer(20);
                    timer.start();
                    lapse_spawn = 3;
                    spawn_counter = 0;
                    next_lemming = 0;
                }
                DrawLemming::Instance().Refresh_level(Console.buffer);

                //todo:reset lemmings list & fix background lemmings interaction
                DrawLemming::Instance().DrawLemmings(Console.buffer, timer);
                if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&    
                    spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                    next_lemming<DrawLemming::Instance().lemmings.size())
                {
                    DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                    next_lemming++;
                }
            }
            else if (DrawLemming::Instance().current_screen == LEVEL_THREE)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    timer = NYTimer(20);
                    timer.start();
                    lapse_spawn = 3;
                    spawn_counter = 0;
                    next_lemming = 0;
                }
                DrawLemming::Instance().Refresh_level(Console.buffer);

                //todo:reset lemmings list & fix background lemmings interaction
                DrawLemming::Instance().DrawLemmings(Console.buffer, timer);
                if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&    
                    spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                    next_lemming<DrawLemming::Instance().lemmings.size())
                {
                    DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                    next_lemming++;
                }
            }
            DrawLemming::Instance().last_screen = DrawLemming::Instance().current_screen;
            spawn_counter = static_cast<int>(timer.getElapsedMs() / 1000);
            input.play_frame(Console.buffer, input.mouseState);
        }
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord,
                           &Console.rcRegion);
        input.ProcessInput(DrawLemming::Instance().lemmings, Console.buffer, timer);
    }        
}
