#pragma once
#include "Element.h"

enum TypeSkillButton
{
    NOTHING,
    DIG_BUTTON,
    UMBRELLA_BUTTON,
    WAIT_BUTTON,
    BOOM_BUTTON
};

class SkillButton : public Element
{
public:
    SkillButton(TypeSkillButton type_button, COORD pos);
    void resetEtat();
    void onPress();
    TypeSkillButton type_button;
    bool is_active = false;
    Animation buttonUp;
    Animation buttonDown;
};
