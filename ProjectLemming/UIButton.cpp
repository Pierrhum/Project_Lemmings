#include "UIButton.h"

#include "DrawLemming.h"

void UIButton::onPress()
{
    isPressed = true;

    switch (action)
    {
    case PLAY:
            DrawLemming::Instance().LoadLevel(1);
            break;
        case RETURN_MENU:
            DrawLemming::Instance().current_screen = MENU;
            break;
        case REPLAY:
            //todo :Current screen become current level 
            DrawLemming::Instance().current_screen = LEVEL_ONE;
            break;
        case NEXT:
            //todo :Current screen become next level 
            DrawLemming::Instance().current_screen = LEVEL_TWO;
            break;
        // case QUIT:
        //     break;
    }
}
