#include "UIButton.h"

#include "DrawLemming.h"

void UIButton::onPress()
{
    mciSendString(TEXT("play sound/OK.wav"), NULL, 0, NULL);
    
    switch (action)
    {
        case PLAY:
            DrawLemming::Instance().LoadScene(LEVEL_ONE);
            break;
        case RETURN_MENU:
            DrawLemming::Instance().LoadScene(MENU);
            break;
        case REPLAY:
            DrawLemming::Instance().LoadScene(DrawLemming::Instance().currentLevel);
            break;
        case NEXT:
            if(DrawLemming::Instance().currentLevel == 3) DrawLemming::Instance().LoadScene(MENU);
            else DrawLemming::Instance().LoadScene(DrawLemming::Instance().currentLevel + 1);
            break;
        case QUIT:
            exit(EXIT_SUCCESS);
            break;
    }
}
