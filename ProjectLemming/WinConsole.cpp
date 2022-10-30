#include "WinConsole.h"

WinConsole::WinConsole()
{
    hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE );
    hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );
    dwBufferSize = { 200,100 };
    rcRegion = { 0, 0, (short)(dwBufferSize.X-1), (short)(dwBufferSize.Y-1) };
    hwnd_console = GetConsoleWindow();

    buffer.resize(dwBufferSize.Y, std::vector<CHAR_INFO>(dwBufferSize.X));
    CHAR_INFO c;
    flat_vect.resize(dwBufferSize.Y * dwBufferSize.X, c);

    SetConsoleMode(hInput, fdwMode);
    FlushConsoleInputBuffer(hInput);
    
    SetConsoleTitleA("The Lemmings");
    SetConsoleScreenBufferSize(hOutput, dwBufferSize);
    SetConsoleWindowInfo(hOutput, true, &rcRegion);
    //ShowWindow(hwnd_console,SW_MAXIMIZE);
}
