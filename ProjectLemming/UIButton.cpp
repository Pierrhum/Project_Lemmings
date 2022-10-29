#include "UIButton.h"

#include "DrawLemming.h"

void UIButton::onPress()
{
    switch (action)
    {
        case PLAY:
            DrawLemming::Instance().LoadLevel(LEVEL_ONE);
            break;
        case RETURN_MENU:
            DrawLemming::Instance().LoadLevel(MENU);
            break;
        case REPLAY:
            DrawLemming::Instance().LoadLevel(DrawLemming::Instance().currentLevel);
            break;
        case NEXT:
            if(DrawLemming::Instance().currentLevel == 3) DrawLemming::Instance().LoadLevel(MENU);
            else DrawLemming::Instance().LoadLevel(DrawLemming::Instance().currentLevel + 1);
            break;
        case QUIT:
            exit(EXIT_SUCCESS);
            break;
    }
}
