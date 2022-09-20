#pragma once
#include <windows.h>
#include "NYTimer.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Input
{
private:
    DWORD fdwMode;
    HANDLE hInput;
    COORD MousePos;
    bool MouseInit;
    
public:
    Input();
    void DrawMouse(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], bool erase);
    void ProcessInput(CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH], NYTimer timer);
};
