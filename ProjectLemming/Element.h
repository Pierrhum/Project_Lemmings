#pragma once
#include "Animation.h"

class Element
{
protected:
    bool debugOutline = false;
public:
    COORD POS;
    
    vector<Animation*> animations;
    int current_anim = 0;
    int loop;
    bool end_anim = false;
    int next_frame_to_play = 0;
    
    Element(vector<Animation*> animations, COORD POS, int loop = true) : animations(animations), POS(POS), loop(loop){}
    Element(Animation* anim, COORD POS, int loop = true) : POS(POS), loop(loop)
    {
        animations.push_back(anim);
    }
    void play_next_frame(std::vector<std::vector<CHAR_INFO>>& buffer);
    COORD get_center();
};
