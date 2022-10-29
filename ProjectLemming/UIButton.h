#pragma once
#include "Element.h"

class UIButton : public Element
{
public:
    enum ButtonAction { PLAY, QUIT, RETURN_MENU, REPLAY, NEXT };
    ButtonAction action;
    
    UIButton(Animation* image, COORD POS, ButtonAction _action) : Element(image,POS,false), action(_action) {}
    void onPress();
};
