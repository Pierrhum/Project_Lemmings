#include "SkillButton.h"

#include "DrawLemming.h"

SkillButton::SkillButton(TypeButton type_button, COORD POS) : type_button(type_button), POS(POS)
{
    if (type_button == DIG_BUTTON)
    {
        buttonUp = Picture("spriteAscii/button/DigButtonUp.txt");
        buttonDown = Picture("spriteAscii/button/DigButtonDown.txt");
    }
}

void SkillButton::PressButton()
{
    is_active = !is_active;
}

void SkillButton::ShowButton(std::vector<std::vector<CHAR_INFO>>& buffer)
{
    if (is_active)
    {
        DrawLemming::Instance().DrawPicture(buffer, POS.X, POS.Y, buttonDown);
    }
    else
    {
        DrawLemming::Instance().DrawPicture(buffer, POS.X, POS.Y, buttonUp);
    }
}

