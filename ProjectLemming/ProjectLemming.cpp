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
    NYTimer timer(10);
    timer.start();

    //ShowCursor(FALSE);
    ReadConsoleOutput( Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize,
                        Console.dwBufferCoord, &Console.rcRegion );
    
    Picture picture("spriteAscii/background/background200_100.txt");
    DrawLemming::Instance().intial_level = picture;


    Element drop(new Animation("spriteAscii/drop/drop16.txt", 10), COORD{50, 20}, false);
    Element door(new Animation("spriteAscii/door/door16.txt", 6), COORD{100, 35}, true); // 145, 67
    
    short borderMap = (short)DrawLemming::Instance().intial_level.w_picture;
    Element minute(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 23), 5}, false);
    Element sec1(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 15), 5}, false);
    Element sec2(new Animation("spriteAscii/numbers.txt", 10), COORD{(short)(borderMap - 10), 5}, false);
    

    vector<Animation*> _anims;
    _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8));
    _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8, true));
    _anims.push_back( new Animation("spriteAscii/lemming_fall/lem_fall_size8.txt", 4));
    _anims.push_back( new Animation("spriteAscii/lemming_dig/lem_dig_size10.txt", 16));
    _anims.push_back( new Animation("spriteAscii/lemming_end/lem_end10.txt", 8));
    
    COORD centre_drop_lem{(short)(drop.get_center().X - _anims.at(2)->get_frame(0).w_picture/2), (short)(drop.get_center().Y - _anims.at(2)->get_frame(0).h_picture/2)};
    static Lemming lemming = Lemming(_anims, centre_drop_lem, FALL);
    
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

            if (drop.end_anim) lemming.Update(Console.buffer);
            if(lemming.isOverlapping(door, true)) MessageBox(NULL,_T("Victory!"),_T("Lemmings"),MB_OK);

            // Gestion du timer
            int _minute = timer.getRemainingTime() / 60;
            int _seconde = timer.getRemainingTime() - (_minute * 60);
            // Affichage
            minute.play_frame(Console.buffer, _minute);
            sec1.play_frame(Console.buffer, _seconde / 10);
            sec2.play_frame(Console.buffer, _seconde % 10);
            
            
        }
        
        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        
        if(timer.getRemainingTime() == 0)
            MessageBox(NULL,_T("Looser!"),_T("Lemmings"),MB_OK);
        
        input.ProcessInput(lemming, Console.buffer, timer);        
    }
}