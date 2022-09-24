#pragma once
#include "Animation.h"

class Element
{
public:
    Animation* anim;
    COORD POS;
    int loop;
    bool end_anim = false;
    int next_frame_to_play = 0;
    Element(Animation* anim, COORD POS, int loop = true) : anim(anim), POS(POS), loop(loop){}
    void play_next_frame(std::vector<std::vector<CHAR_INFO>>& buffer);
    COORD get_center();
};
