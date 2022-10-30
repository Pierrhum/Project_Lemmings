#pragma once

#include <vector>

#include "Picture.h"

using namespace std;

/**
* \brief Make a vector list of Picture to save all frame on it.
 */
class Animation
{    
public:
    Picture origin_picture;
    int nb_frames;
    vector<Picture> vanim;
    Animation(){}
    Animation(const char* str_file, int nb_frames, bool flipped = false);
    Picture get_frame(int num_fram);
};
