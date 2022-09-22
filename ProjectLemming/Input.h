#pragma once
#include "NYTimer.h"
#include "WinConsole.h"
#include "DrawLemming.h"

class Input
{
private:
    WinConsole &Console;
    COORD MousePos;
    bool MouseInit;
    
public:
    Input(WinConsole &WinConsole) : Console(WinConsole) { }
    void DrawMouse(std::vector<std::vector<CHAR_INFO>>& buffer, bool erase, bool onClick);
    void ProcessInput(std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer);

    Hexa_color GetHexaColor(Picture pic, int x, int y);
};
