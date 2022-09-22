#include "Animation.h"

Animation::Animation(const char* str_file, int nb_frames): nb_frames(nb_frames), origin_picture(Picture(str_file))
{
    vector<int> frame_buffer;
    for (int i = 0; i < origin_picture.h_picture * origin_picture.w_picture; ++i)
    {
        frame_buffer.push_back(origin_picture.vpicture.at(i));
        if (i >= (vanim.size()+1)*(origin_picture.h_picture/nb_frames)*origin_picture.w_picture)
        { 
            vanim.push_back(Picture(frame_buffer, origin_picture.w_picture, origin_picture.h_picture/nb_frames));
            frame_buffer.clear();
        }
    }
}

Picture Animation::get_frame(int num_fram)
{
    return vanim.at(num_fram);
}

