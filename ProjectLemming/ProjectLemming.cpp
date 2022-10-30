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

int last_second = 0;
int timing_frame = 100;
int lapse_spawn = 3, spawn_counter = 0, next_lemming = 0;

void LemmingUpdate(WinConsole& Console, NYTimer& timer)
{
    DrawLemming::Instance().DrawLemmings(Console.buffer);
    if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&    
        spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
        next_lemming<DrawLemming::Instance().lemmings.size())
    {
        DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
        next_lemming++;
    }
}

void ResetValues(NYTimer& timer)
{
    last_second = static_cast<int>(timer.getElapsedMs() / timing_frame);
    lapse_spawn = 3;
    spawn_counter = 0;
    next_lemming = 0;
}

int main()
{
    WinConsole Console;
    Input input(Console);
    NYTimer timer;

    ReadConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                      Console.dwBufferCoord, &Console.rcRegion);
    
    
    DrawLemming::Instance().LoadScene(MENU);
    timer.start();
    
    while (1)
    {
        if (static_cast<int>(timer.getElapsedMs() / timing_frame) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedMs() / timing_frame);

            // Title Screen
            if (DrawLemming::Instance().current_screen == MENU)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    next_lemming = 0;
                    spawn_counter = 0;
                }
                DrawLemming::Instance().Refresh_menu(Console.buffer);
                
                LemmingUpdate(Console, timer);
            }
            
            // Win Screen
            else if (DrawLemming::Instance().current_screen == WIN)
                DrawLemming::Instance().Refresh_win(Console.buffer);
            
            // Game Over Screen
            else if (DrawLemming::Instance().current_screen == LOOSE)
                DrawLemming::Instance().Refresh_lose(Console.buffer);
            
            // First Level
            else if (DrawLemming::Instance().current_screen == LEVEL_ONE)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    timer.restart(90);
                    ResetValues(timer);
                }
                else if(timer.getRemainingTime() <= 0)
                    DrawLemming::Instance().LoadScene(LOOSE);
                else
                {
                    DrawLemming::Instance().Refresh_level(Console.buffer, timer);          
                    LemmingUpdate(Console, timer);                    
                }
            }
            
            // Second Level
            else if (DrawLemming::Instance().current_screen == LEVEL_TWO)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    timer.restart(80);
                    ResetValues(timer);
                }
                else if(timer.getRemainingTime() <= 0)
                    DrawLemming::Instance().LoadScene(LOOSE);
                else
                {
                    DrawLemming::Instance().Refresh_level(Console.buffer, timer);      
                    LemmingUpdate(Console, timer);                       
                }
            }
            
            // Third Level
            else if (DrawLemming::Instance().current_screen == LEVEL_THREE)
            {
                if (DrawLemming::Instance().last_screen != DrawLemming::Instance().current_screen)
                {
                    timer.restart(200);
                    ResetValues(timer);
                }
                else if(timer.getRemainingTime() <= 0)
                    DrawLemming::Instance().LoadScene(LOOSE);
                else
                {
                    DrawLemming::Instance().Refresh_level(Console.buffer, timer);      
                    LemmingUpdate(Console, timer);                    
                }
            }
            
            DrawLemming::Instance().last_screen = DrawLemming::Instance().current_screen;
            spawn_counter = static_cast<int>(timer.getElapsedMs() / 1000);
            input.play_frame(Console.buffer, input.mouseState);
        }
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord,
                           &Console.rcRegion);
        input.ProcessInput(DrawLemming::Instance().lemmings);
    }        
}
