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
    enum MouseState { NORMAL = 0, HOVER = 1, CLICK = 2 };
    MouseState mouseState = NORMAL;
    
    Input(WinConsole &WinConsole) : Console(WinConsole), Element(new Animation("spriteAscii/mouse.txt", 3), COORD{100, 5}, false) { }
    void ProcessInput(vector<Lemming>& lemmings, std::vector<std::vector<CHAR_INFO>>& buffer, NYTimer timer);

    Hexa_color GetHexaColor(Picture pic, int x, int y);
};
