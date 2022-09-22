#pragma once

#include <vector>

#include "DrawLemming.h"
#include "Picture.h"

using namespace std;

class Animation
{
public:
    int nb_frames;
    Picture origin_picture;
    vector<Picture> vanim;
    Animation(const char* str_file, int nb_frames);
    void play_anim(std::vector<std::vector<CHAR_INFO>> &buffer, int cpt, bool loop);
    Picture get_frame(int num_fram);
};
