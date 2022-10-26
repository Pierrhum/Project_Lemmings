#pragma once
#include "Element.h"

class UIButton : public Element
{
public:
    enum ButtonAction { PLAY, QUIT };
    ButtonAction action;
    bool isPressed = false;
    
    UIButton(Animation* image, COORD POS, ButtonAction _action) : Element(image,POS,false), action(_action) {}
    void onPress();
};
