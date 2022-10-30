#pragma once
#include "Element.h"

class UIButton : public Element
{
public:
    /**
     * \brief Action of the button, that will call the corresponding effect
     */
    enum ButtonAction { PLAY, QUIT, RETURN_MENU, REPLAY, NEXT };
    ButtonAction action;
    
    UIButton(Animation* image, COORD POS, ButtonAction _action) : Element(image,POS,false), action(_action) {}

    /**
     * \brief Call the action when the button is pressed
     */
    void onPress();
};
