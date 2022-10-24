#pragma once
#include "NYTimer.h"
#include "WinConsole.h"
#include "DrawLemming.h"
#include "Lemming.h"

class Input
{
private:
    WinConsole &Console;
    COORD MousePos;
    bool MouseInit;
    
public:
    Input(WinConsole &WinConsole) : Console(WinConsole) { }
    void DrawMouse(std::vector<std::vector<CHAR_INFO>>& buffer, bool erase, bool onClick);
    void ProcessInput(vector<Lemming>& lemmings, std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer);
    bool isOverlappingLemming(Lemming& lemming);

    Hexa_color GetHexaColor(Picture pic, int x, int y);
};
