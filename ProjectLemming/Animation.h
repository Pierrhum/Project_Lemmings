#pragma once

#include <vector>

#include "DrawLemming.h"
#include "Picture.h"

using namespace std;

class Animation
{
private:
    int currant_frame = 0;
    
public:
    Picture origin_picture;
    int nb_frames;
    vector<Picture> vanim;
    Animation(const char* str_file, int nb_frames, bool flipped = false);
    Picture get_frame(int num_fram);
};
