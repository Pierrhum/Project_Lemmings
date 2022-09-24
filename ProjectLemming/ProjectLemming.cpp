#define _WIN32_WINNT 0x0501


#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include "Animation.h"
#include "Input.h"
#include "NYTimer.h"
#include "DrawLemming.h"
#include "Element.h"
#include "Lemming.h"

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
    
    Picture picture("spriteAscii/background/background200_100.txt");
    DrawLemming::Instance().intial_level = picture;

    Element drop(new Animation("spriteAscii/drop/drop25.txt", 10), COORD{50, 20}, false);
    Element door(new Animation("spriteAscii/door/door16.txt", 6), COORD{145, 67}, true);

    vector<Animation*> _anims;
    _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8));
    _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8, true));
    _anims.push_back( new Animation("spriteAscii/lemming_fall/lem_fall_size8.txt", 4));
    _anims.push_back( new Animation("spriteAscii/lemming_dig/lem_dig_size10.txt", 16));
    Lemming lemming = Lemming(_anims, COORD{drop.get_center().X, (short)(drop.get_center().Y-10)});
    lemming.change_movement(RMOVE);
    
    int last_second = 0;
    int timing_frame = 100;
    while(1)
    {
        if(static_cast<int>(timer.getElapsedMs()/timing_frame) > last_second)
        {
            last_second = static_cast<int>(timer.getElapsedMs()/timing_frame);
            DrawLemming::Instance().Refresh_init_level(Console.buffer);
            drop.play_next_frame(Console.buffer);
            door.play_next_frame(Console.buffer);

            if (drop.end_anim) lemming.play_next_frame(Console.buffer);
        }
        
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        input.ProcessInput(Console.buffer, timer);        
    }
}