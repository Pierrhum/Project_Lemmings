#pragma once
#include "NYTimer.h"
#include "WinConsole.h"
#include "DrawLemming.h"
#include "Lemming.h"

/**
 * \brief Class managing the mouse input actions, and its display.
 */
class Input : public Element
{
private:
    WinConsole &Console;
    COORD MousePos;
    
public:
    enum MouseState { NORMAL = 0, HOVER = 1, CLICK = 2 };
    MouseState mouseState = NORMAL;
    
    Input(WinConsole &WinConsole) : Console(WinConsole), Element(new Animation("spriteAscii/mouse.txt", 3), COORD{100, 5}, false) { }
    
    /**
     * \brief Manage the input actions, and the MouseState
     * \param lemmings : Lemmings present in the current map
     */
    void ProcessInput(vector<Lemming>& lemmings);

    /**
     * \brief Check if the Skill Button overlaps the input, and set it as the selected skill if it does, then reset the others
     * \param skill_button : Skill button receiving the click
     */
    void ActionSkillButton(SkillButton& skill_button);

    /**
     * \brief Check if a Lemming overlaps the input, and call the chosen skill action if it does
     * \param lemmings : Lemmings present in the current map
     */
    void ActionSkillLemming(vector<Lemming>& lemmings);
};
