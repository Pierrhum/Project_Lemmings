#pragma once
#include "NYTimer.h"
#include "WinConsole.h"
#include "DrawLemming.h"
#include "Lemming.h"

class Input : public Element
{
private:
    WinConsole &Console;
    COORD MousePos;
    bool MouseInit;
    
public:
    Input(WinConsole &WinConsole) : Console(WinConsole), Element(new Animation("spriteAscii/mouse.txt", 3), COORD{100, 5}, false) { }
    void DrawMouse(std::vector<std::vector<CHAR_INFO>>& buffer, bool erase, bool onClick);
    void ProcessInput(vector<Lemming>& lemmings, std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer);
    bool isOverlappingLemming(Lemming& lemming);
    bool onClick = false;

    Hexa_color GetHexaColor(Picture pic, int x, int y);
};
