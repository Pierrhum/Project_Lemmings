#include "Animation.h"

Animation::Animation(const char* str_file, int nb_frames, bool flipped): origin_picture(Picture(str_file)), nb_frames(nb_frames)
{
    vector<int> frame_buffer;
    if (flipped) origin_picture.flip_picture();
    for (int i = 0; i < origin_picture.h_picture * origin_picture.w_picture; ++i)
    {
        frame_buffer.push_back(origin_picture.get_pixel(i));
        
        if (i >= (vanim.size()+1)*(origin_picture.h_picture/nb_frames)*origin_picture.w_picture-1)
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

