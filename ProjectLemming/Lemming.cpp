#include "Lemming.h"
#include "DrawLemming.h"


void Lemming::Update(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    //const int index_anim = next_frame_to_play % movements[currant_state].lem_vector_list.size();
    //DrawLemming::Instance().DrawPicture(buffer, POS.X += movements[currant_state].lem_vector_list[index_anim].X,
    //                                    POS.Y += movements[currant_state].lem_vector_list[index_anim].Y,
    //                                    animations.at(currant_state)->get_frame(next_frame_to_play));
    //next_frame_to_play++;
    //if (next_frame_to_play>=animations.at(currant_state)->nb_frames) next_frame_to_play = 0;
    
    State oldState = current_state;
    switch (current_state)
    {
        case DIG:
            if(!isColliding(BOTTOM))
                current_state = FALL;
            else Dig();
        break;
        case FALL:
            if(isColliding(BOTTOM))
                current_state = fall_state;
        break;
        case RMOVE:
            if(!isColliding(BOTTOM))
                current_state = FALL;
            else if(isColliding(RIGHT))
            {
                if(canClimb(RIGHT))
                    POS.Y -= 1;
                else
                    current_state = fall_state = LMOVE;
            }
        break;

        case LMOVE:
            if(!isColliding(BOTTOM))
                current_state = FALL;
            else if(isColliding(LEFT))
            {
                if(canClimb(LEFT))
                    POS.Y -= 1;
                else
                    current_state = fall_state = RMOVE; 
            }
        break;
    }
    
    if(oldState != current_state)
    {
        Picture pic = animations.at(current_state)->origin_picture;
        SIZE.X = (short)pic.w_picture;
        SIZE.Y = (short)pic.h_picture/animations.at(current_state)->nb_frames;
    }
    if(current_state == DIG)
        play_next_frame(buffer, {-3,0});
    else play_next_frame(buffer);
    current_anim = current_state;
    POS.X += movements[current_state].lem_vector.X;
    POS.Y += movements[current_state].lem_vector.Y;
}

void Lemming::Dig()
{
    for(int x = POS.X; x < POS.X + SIZE.X; x++)
        DrawLemming::Instance().intial_level.set_pixel(x, POS.Y + SIZE.Y, BLACK);
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

    default:
        return false;
    }
}