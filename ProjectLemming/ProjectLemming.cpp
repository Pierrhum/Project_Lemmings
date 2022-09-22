#define _WIN32_WINNT 0x0501
#include <tchar.h>

#include "Input.h"
#include "NYTimer.h"
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
    
    Console.buffer[5][10].Char.AsciiChar = 'H';
    Console.buffer[5][10].Attributes = 0x0E;
    Console.buffer[5][11].Char.AsciiChar = 'i';
    Console.buffer[5][11].Attributes = 0x0B;
    Console.buffer[5][12].Char.AsciiChar = '!';
    Console.buffer[5][12].Attributes = 0x0A;
    for(int y=0;y < Console.dwBufferSize.Y; y++)
    {
        Console.buffer[y][0].Char.AsciiChar = '|';
        Console.buffer[y][0].Attributes = 0x0A;
        Console.buffer[y][Console.dwBufferSize.X-1].Char.AsciiChar = '|';
        Console.buffer[y][Console.dwBufferSize.X-1].Attributes = 0x0A;
    }
    
    for(int x=0; x < Console.dwBufferSize.X;x++)
    {
        Console.buffer[0][x].Char.AsciiChar = '-';
        Console.buffer[0][x].Attributes = 0x0A;
        Console.buffer[Console.dwBufferSize.Y-1][x].Char.AsciiChar = '-';
        Console.buffer[Console.dwBufferSize.Y-1][x].Attributes = 0x0A;
    }

    while(1)
    {
        if(static_cast<int>(timer.getElapsedSeconds()) % 2 == 0)
        {
            Console.buffer[5][10].Attributes = 0x0E;
        } else 
            Console.buffer[5][10].Attributes = 0x0B;

        WriteConsoleOutput(Console.hOutput, Console.GetFlatBuffer(), Console.dwBufferSize, Console.dwBufferCoord, &Console.rcRegion );
        input.ProcessInput(Console.buffer, timer);        
    }
}