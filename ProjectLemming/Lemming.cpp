#include "Lemming.h"


void Lemming::Update(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    State oldState = current_state;
    
    switch (current_state)
    {
        case FALL:
            if(isColliding(BOTTOM))
                current_state = fall_state;
        break;
        case RMOVE:
            if(!isColliding(BOTTOM))
            {
                current_state = FALL;
                fall_state = RMOVE;
            }
            else if(isColliding(RIGHT))
            {
                if(canClimb(RIGHT))
                    POS.Y -= 1;
                else
                    current_state = LMOVE;
            }
        break;

        case LMOVE:
            if(!isColliding(BOTTOM))
            {
                current_state = FALL;
                fall_state = LMOVE;
            }
            else if(isColliding(LEFT))
            {
                if(canClimb(LEFT))
                    POS.Y -= 1;
                else
                    current_state = RMOVE;
            }
        break;
    }
    
    if(oldState != current_state)
    {
        Picture pic = animations.at(current_state)->origin_picture;
        SIZE.X = (short)pic.w_picture;
        SIZE.Y = (short)pic.h_picture/animations.at(current_state)->nb_frames;
    }
    
    play_next_frame(buffer);
    current_anim = current_state;
    POS.X += movements[current_state].lem_vector.X;
    POS.Y += movements[current_state].lem_vector.Y;
    
}

bool Lemming::isColliding(SIDES side) const
{
    int collidingPixels = 0;
    switch (side)
    {
    case BOTTOM :
        for(int x = POS.X; x < POS.X + SIZE.X; x++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( x,POS.Y + SIZE.Y) != BLACK ? 1 : 0;
        return collidingPixels > SIZE.X / 2;
    case TOP:
        for(int x = POS.X; x < POS.X + SIZE.X; x++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( x,POS.Y) != BLACK ? 1 : 0;
        return collidingPixels > SIZE.X / 2;
    case RIGHT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( POS.X + SIZE.X, y) != BLACK ? 1 : 0;
        return collidingPixels >= SIZE.Y / 4;
    case LEFT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( POS.X, y) != BLACK ? 1 : 0;
        return collidingPixels >= SIZE.Y / 4;
    }
    return false;
}

bool Lemming::canClimb(SIDES side) const
{
    int collidingPixels = 0;
    
    switch (side)
    {
    case RIGHT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( POS.X + SIZE.X, y) != BLACK ? 1 : 0;
        return collidingPixels == SIZE.Y / 4 && !isColliding(TOP);
        
    case LEFT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( POS.X, y) != BLACK ? 1 : 0;
        
        return collidingPixels == SIZE.Y / 4 && !isColliding(TOP);
        
    case BOTTOM :
    case TOP :
        return false;
    }
}
