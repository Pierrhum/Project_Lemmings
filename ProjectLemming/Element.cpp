#include "Element.h"

void Element::play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer)
{
    if (!loop)
    {
        if (next_frame_to_play<animations[current_anim]->nb_frames-1) next_frame_to_play++;
        else end_anim = true;
    } else
    {
        next_frame_to_play++;
        if (next_frame_to_play>=animations[current_anim]->nb_frames) next_frame_to_play = 0;
    }
    DrawLemming::Instance().DrawPicture(buffer, POS.X, POS.Y, animations[current_anim]->get_frame(next_frame_to_play), debugOutline);
}

COORD Element::get_center()
{
    return COORD{(short)(POS.X + animations[current_anim]->origin_picture.w_picture/2), (short)( POS.Y + animations[current_anim]->origin_picture.h_picture / animations[current_anim]->nb_frames/2)};
}