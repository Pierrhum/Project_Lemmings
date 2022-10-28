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
            DrawLemming::Instance().LoadLevel(MENU);
            break;
        case REPLAY:
            //todo :Current screen become current level 
            DrawLemming::Instance().LoadLevel(DrawLemming::Instance().currentLevel);
            break;
        case NEXT:
            //todo :Current screen become next level 
            DrawLemming::Instance().LoadLevel(DrawLemming::Instance().currentLevel + 1);
            break;
        // case QUIT:
        //     break;
    }
}
