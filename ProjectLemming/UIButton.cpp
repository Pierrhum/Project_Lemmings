#include "UIButton.h"

#include "DrawLemming.h"

void UIButton::onPress()
{
    isPressed = true;

    switch (action)
    {
    case PLAY:
            DrawLemming::Instance().is_title_screen = false;
            break;
        case QUIT:
            break;
    }
}
