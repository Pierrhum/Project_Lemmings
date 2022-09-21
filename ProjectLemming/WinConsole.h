#pragma once
#include "windows.h"

class WinConsole
{
private:
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
public:
    SHORT SCREEN_HEIGHT = 0;
    SHORT SCREEN_WIDTH = 0;
    HWND hwnd_console;
    HANDLE hOutput;
    HANDLE hInput;

    CHAR_INFO** buffer;

    WinConsole();
    LONG_PTR setConsoleWindowStyle(INT n_index,LONG_PTR new_style);
    
};
