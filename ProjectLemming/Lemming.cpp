﻿#include "Lemming.h"
#include "DrawLemming.h"


void Lemming::Update(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    if(!is_showed) return;
    
    int index_anim = next_frame_to_play % movements[current_state].lem_vector_list.size();
    
    State oldState = current_state;
    switch (current_state)
    {
        case WAIT:
            
        break;
        case CRASH:
            
        break;
        case BOOM:
            
        break;
        case DIG:
            if(!isColliding(BOTTOM))
                if (is_umbrellaed)
                    current_state = UMBRELLA;
                else
                    current_state = FALL;
            // Si la frame permet un déplacement vers le bas, on creuse le niveau
            else if(movements[current_state].lem_vector_list[index_anim].Y == 1) 
                Dig();
        break;
        case FALL :
            fallDistance++;
            if(isColliding(BOTTOM))
                if(fallDistance > 30) current_state = CRASH;
                else
                {
                    current_state = fall_state;
                    fallDistance = 0;
                }
        break;
        case UMBRELLA:
            if(isColliding(BOTTOM))
                current_state = fall_state;
        break;
        case RMOVE:
            if(!isColliding(BOTTOM))
                if (is_umbrellaed)
                    current_state = UMBRELLA;
                else
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
                if (is_umbrellaed)
                    current_state = UMBRELLA;
                else
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
        index_anim = next_frame_to_play % movements[current_state].lem_vector_list.size();
    }
    current_anim = current_state;
    if(oldState == DIG)
        play_next_frame(buffer, {-3,0});
    else if (oldState == UMBRELLA)
        play_next_frame(buffer, {2, 0}, 4);
    else if (oldState == CRASH)
        if(next_frame_to_play==animations[CRASH]->nb_frames-1) is_showed = false;
        else play_next_frame(buffer, {-4, 0}, 16);
    else play_next_frame(buffer);
    
    POS.X += movements[current_state].lem_vector_list[index_anim].X;
    POS.Y += movements[current_state].lem_vector_list[index_anim].Y;
}

void Lemming::Dig()
{
    for(int x = POS.X; x < POS.X + SIZE.X; x++)
        DrawLemming::Instance().initial_level.set_pixel(x, POS.Y + SIZE.Y, BLACK);
}

bool Lemming::isColliding(SIDES side) const
{
    int collidingPixels = 0;
    switch (side)
    {
    case BOTTOM :
        for(int x = POS.X; x < POS.X + SIZE.X; x++)
            collidingPixels += DrawLemming::Instance().initial_level.get_pixel( x,POS.Y + SIZE.Y) != BLACK ? 1 : 0;
        return collidingPixels > SIZE.X / 2;
    case TOP:
        for(int x = POS.X; x < POS.X + SIZE.X; x++)
            collidingPixels += DrawLemming::Instance().initial_level.get_pixel( x,POS.Y) != BLACK ? 1 : 0;
        return collidingPixels > SIZE.X / 2;
    case RIGHT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().initial_level.get_pixel( POS.X + SIZE.X, y) != BLACK ? 1 : 0;
        return collidingPixels >= SIZE.Y / 4;
    case LEFT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().initial_level.get_pixel( POS.X, y) != BLACK ? 1 : 0;
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
            collidingPixels += DrawLemming::Instance().initial_level.get_pixel( POS.X + SIZE.X, y) != BLACK ? 1 : 0;
        return collidingPixels == SIZE.Y / 4 && !isColliding(TOP);
        
    case LEFT :
        for(int y = POS.Y; y < POS.Y + SIZE.Y; y++)
            collidingPixels += DrawLemming::Instance().initial_level.get_pixel( POS.X, y) != BLACK ? 1 : 0;
        
        return collidingPixels == SIZE.Y / 4 && !isColliding(TOP);

    default:
        return false;
    }
}

void Lemming::exitLevel() 
{
    current_state = END;
    is_showed = false;
}
