#include "Picture.h"

#include <fstream>
#include <string>

using namespace std;

/**
 * \brief Import Picture from TXT file string name
 * \param str_file Call txtFile with pixels anim info
 */
Picture::Picture(const char* str_file)
{
    ifstream input;
    input.open(str_file);

    if (input.is_open() == true) {
        string word;
        input >> word;
        w_picture = stoi(word);
        input >> word;
        h_picture = stoi(word);
        input >> word;
        
        for (int i = 0; i < h_picture*w_picture; ++i)
        {
            input >> word;
            vpicture.push_back(stoi(word));
        }
    }
    input.close();
}

void Picture::flip_picture()
{
    vector<int> flipped_pict_buffer;
    for (int i = 0; i < w_picture*h_picture; ++i)
    {
        flipped_pict_buffer.push_back(vpicture.at(w_picture*(i/w_picture+1)-1-i%w_picture));
    }
    vpicture = flipped_pict_buffer;
}

int Picture::get_pixel(int i)
{
    return vpicture.at(i);
}

int Picture::get_pixel(int x, int y)
{
    
    return y*w_picture + x < vpicture.size() ? vpicture.at(y*w_picture + x) : NULL;
}

void Picture::set_pixel(int x, int y, int color)
{
    if(y*w_picture + x < vpicture.size())
        vpicture[y*w_picture + x] = color;
    
}
