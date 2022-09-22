#pragma once

#include <vector>

#include "Picture.h"

using namespace std;

class Animation
{
public:
    int nb_frames;
    bool loop = false;
    Picture origin_picture;
    vector<Picture> vanim;
    Animation(const char* str_file, int nb_frames);
    Picture get_frame(int num_fram);
};
