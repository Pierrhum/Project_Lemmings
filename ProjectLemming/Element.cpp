#include "Element.h"
#include "DrawLemming.h"

void Element::play_frame(std::vector<std::vector<CHAR_INFO>>& buffer, int frame)
{
    if(frame<0) frame=0;
    DrawLemming::Instance().DrawPicture(buffer, POS.X, POS.Y, animations[current_anim]->get_frame(frame), debugOutline);
}

void Element::play_next_frame(std::vector<std::vector<CHAR_INFO>>& buffer, COORD gap, int loopOn)
{
    if (!loop)
    {
        if (next_frame_to_play<animations[current_anim]->nb_frames-1) next_frame_to_play++;
        else end_anim = true;
    } else
    {
        next_frame_to_play++;
        if (next_frame_to_play>=animations[current_anim]->nb_frames) next_frame_to_play = loopOn;
    }
    DrawLemming::Instance().DrawPicture(buffer, POS.X + gap.X, POS.Y + gap.Y, animations[current_anim]->get_frame(next_frame_to_play), debugOutline);
    
}

COORD Element::get_center()
{
    return COORD{(short)(POS.X + animations[current_anim]->origin_picture.w_picture/2), (short)( POS.Y + animations[current_anim]->origin_picture.h_picture / animations[current_anim]->nb_frames/2)};
}

// 2D AABB vs AABB overlapping
bool Element::isOverlapping(Element& element, const bool center)
{
    // Just comparing to the other element center
    if(center)
        return !(POS.X > element.get_center().X // is to the right of other
        || POS.X + SIZE.X < element.get_center().X // is to the left of other
        || POS.Y + SIZE.Y < element.get_center().Y // is above other
        || POS.Y  > element.get_center().Y); // is below other
    // Comparing to the whole other element bounding box
    else
        return !(POS.X > element.POS.X + element.SIZE.X // is to the right of other
        || POS.X + SIZE.X < element.POS.X // is to the left of other
        || POS.Y + SIZE.Y < element.POS.Y // is above other
        || POS.Y  > element.POS.Y + element.SIZE.Y); // is below other
}
