﻿#include "Lemming.h"


void Lemming::play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawLemming::Instance().DrawPicture(buffer, POS.X += movements[currant_state].lem_vector.X, POS.Y += movements[currant_state].lem_vector.Y,
                                        animations.at(currant_state)->get_frame(next_frame_to_play));
    next_frame_to_play++;
    if (next_frame_to_play>=animations.at(currant_state)->nb_frames) next_frame_to_play = 0;
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
    return COORD{(short)(POS.X + animations.at(currant_state)->origin_picture.h_picture/animations.at(currant_state)->nb_frames/2),
    (short)(POS.Y + animations.at(currant_state)->origin_picture.w_picture/2)};
}