#pragma once
#include "Animation.h"

class Element
{
protected:
    bool debugOutline = false;
public:
    COORD POS;
    COORD SIZE;
    
    vector<Animation*> animations;
    int current_anim = 0;
    int loop;
    bool end_anim = false;
    int next_frame_to_play = 0;
    
    Element(vector<Animation*> animations, COORD POS, int loop = true) : animations(animations), POS(POS), loop(loop){}
    Element(Animation* anim, COORD POS, int loop = true) : POS(POS), loop(loop)
    {
        animations.push_back(anim);
        
        Picture pic = anim->origin_picture;
        SIZE.X = (short)pic.w_picture;
        SIZE.Y = (short)pic.h_picture/anim->nb_frames;
    }
    
    void play_next_frame(std::vector<std::vector<CHAR_INFO>>& buffer, COORD gap={0,0});
    COORD get_center();
    bool isOverlapping(Element& element, const bool center);
};
