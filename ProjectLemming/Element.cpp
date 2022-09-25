#include "Element.h"

void Element::play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    DrawLemming::Instance().DrawPicture(buffer, POS.X, POS.Y, anim->get_frame(next_frame_to_play));
    if (!loop)
    {
        if (next_frame_to_play<anim->nb_frames-1) next_frame_to_play++;
        else end_anim = true;
    } else
    {
        next_frame_to_play++;
        if (next_frame_to_play>=anim->nb_frames) next_frame_to_play = 0;
    }
}

COORD Element::get_center()
{
    return COORD{(short)(POS.X + anim->origin_picture.w_picture/2), (short)( POS.Y + anim->origin_picture.h_picture/anim->nb_frames/2)};
}