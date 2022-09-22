#pragma once
#include <vector>
#include <windows.h>
#include "NYTimer.h"
#define SCREEN_WIDTH 213
#define SCREEN_HEIGHT 45

class Input
{
private:
    DWORD fdwMode;
    HANDLE hInput;
    COORD MousePos;
    bool MouseInit;
    
public:
    Input();
    void DrawMouse(std::vector<std::vector<CHAR_INFO>>& buffer, bool erase, bool onClick);
    void ProcessInput(std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer);
};
