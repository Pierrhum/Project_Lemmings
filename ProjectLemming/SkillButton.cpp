#include "SkillButton.h"

#include "DrawLemming.h"


SkillButton::SkillButton(TypeSkillButton type_button, COORD pos) : Element(), type_button(type_button)
{
    POS = pos;
    loop = false;
    
    if (type_button == DIG_BUTTON)
    {
        buttonUp = Animation("spriteAscii/button/DigButtonUp.txt", 1);
        buttonDown = Animation("spriteAscii/button/DigButtonDown.txt", 1);
    } else if (type_button == UMBRELLA_BUTTON)
    {
        buttonUp = Animation("spriteAscii/button/UmbrellaButtonUp.txt", 1);
        buttonDown = Animation("spriteAscii/button/UmbrellaButtonDown.txt", 1);
    } else if (type_button == WAIT_BUTTON)
    {
        buttonUp = Animation("spriteAscii/button/WaitButtonUp.txt", 1);
        buttonDown = Animation("spriteAscii/button/WaitButtonDown.txt", 1);
    } else if (type_button == BOOM_BUTTON)
    {
        buttonUp = Animation("spriteAscii/button/BoomButtonUp.txt", 1);
        buttonDown = Animation("spriteAscii/button/BoomButtonDown.txt", 1);
    }
    animations.push_back(&buttonUp);
}

void SkillButton::resetEtat()
{
    is_active = false;
    animations.clear();
    animations.push_back(&buttonUp);
}

void SkillButton::onPress()
{
    is_active = !is_active;
    animations.clear();
    if (is_active)
    {
        DrawLemming::Instance().currentSelectedSkill = type_button;
        animations.push_back(&buttonDown);
    }
    else
    {
        DrawLemming::Instance().currentSelectedSkill = NOTHING;
        animations.push_back(&buttonUp);
    }
}

