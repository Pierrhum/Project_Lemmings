#include "Lemming.h"


void Lemming::Update(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    switch (currant_state)
    {
        case FALL:
            if(isColliding(BOTTOM))
                currant_state = RMOVE;
        break;
        case RMOVE:
            if(!isColliding(BOTTOM))
                currant_state = FALL;
            else if(isColliding(RIGHT))
                currant_state = LMOVE;
        break;

        case LMOVE:
            if(!isColliding(BOTTOM))
                currant_state = FALL;
            else if(isColliding(LEFT))
                currant_state = RMOVE;
        break;
    }
    play_next_frame(buffer);
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
        return collidingPixels > SIZE.Y / 2;
    case LEFT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().intial_level.get_pixel( POS.X, y) != BLACK ? 1 : 0;
        return collidingPixels > SIZE.Y / 2;
    }
    return false;
}

void Lemming::play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    Picture pic = animations.at(currant_state)->origin_picture;
    SIZE.X = (short)pic.w_picture;
    SIZE.Y = (short)pic.h_picture/animations.at(currant_state)->nb_frames;
    
    next_frame_to_play++;
    if (next_frame_to_play>=animations.at(currant_state)->nb_frames) next_frame_to_play = 0;
    
    DrawLemming::Instance().DrawPicture(buffer, POS.X += movements[currant_state].lem_vector.X, POS.Y += movements[currant_state].lem_vector.Y,
                                        animations.at(currant_state)->get_frame(next_frame_to_play), true);
    
}

void Lemming::change_state(State newState)
{
    currant_state = newState;
}

State Lemming::get_state()
{
    return currant_state;
}

COORD Lemming::get_center()
{
    return COORD{(short)(POS.X + animations.at(currant_state)->origin_picture.w_picture/2),
    (short)(POS.Y + animations.at(currant_state)->origin_picture.h_picture/animations.at(currant_state)->nb_frames/2)};
}