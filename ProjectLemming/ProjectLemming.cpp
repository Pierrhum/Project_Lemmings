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

    
    short borderMap = (short)DrawLemming::Instance().intial_level.w_picture;
    Element minute(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 23), 5}, false);
    Element sec1(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 15), 5}, false);
    Element sec2(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 10), 5}, false);
    
    int last_second = 0;
    int timing_frame = 100;
    int lapse_spawn = 3;
    int spawn_counter = 0;
    int next_lemming = 0;
    while (1)
    {
        if (static_cast<int>(timer.getElapsedMs() / timing_frame) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedMs() / timing_frame);
            DrawLemming::Instance().Refresh_level(Console.buffer);
            DrawLemming::Instance().drop.play_next_frame(Console.buffer);
            DrawLemming::Instance().door.play_next_frame(Console.buffer);

            DrawLemming::Instance().DrawLemmings(Console.buffer);
            if (static_cast<int>(timer.getElapsedMs() / 1000) != spawn_counter &&
                spawn_counter%lapse_spawn==lapse_spawn-1-2 &&
                next_lemming<DrawLemming::Instance().lemmings.size())
            {
                DrawLemming::Instance().lemmings[next_lemming].is_showed = true;
                next_lemming++;
            }
            spawn_counter = static_cast<int>(timer.getElapsedMs() / 1000);
        }

        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord,
                           &Console.rcRegion);
        input.ProcessInput(Console.buffer, timer);
           
            //if (drop.end_anim) lemming.Update(Console.buffer);
            //if(lemming.isOverlapping(door, true)) MessageBox(NULL,_T("Victory!"),_T("Lemmings"),MB_OK);

            // Gestion du timer
            //int _minute = timer.getRemainingTime() / 60;
            //int _seconde = timer.getRemainingTime() - (_minute * 60);
            // Affichage
            //minute.play_frame(Console.buffer, _minute);
            //sec1.play_frame(Console.buffer, _seconde / 10);
            //sec2.play_frame(Console.buffer, _seconde % 10);
            
            
        }
        
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        
        if(timer.getRemainingTime() == 0)
            MessageBox(NULL,_T("Looser!"),_T("Lemmings"),MB_OK);
        
        input.ProcessInput(lemming, Console.buffer, timer);        
    }
}
