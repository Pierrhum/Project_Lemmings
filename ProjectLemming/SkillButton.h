#pragma once

#include <windows.h>

#include "Picture.h"

enum TypeButton
{
    DIG_BUTTON,
    BRIDGE_BUTTON,
    JUMP_BUTTON
};

class SkillButton
{
public:
    SkillButton(TypeButton type_button, COORD POS);
    void PressButton();
    void ShowButton(std::vector<std::vector<CHAR_INFO>>& buffer);
    TypeButton type_button;
    COORD POS;
    bool is_active = false;
    Picture buttonUp;
    Picture buttonDown;
};
