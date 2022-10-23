#pragma once
#include <vector>

using namespace std;

class Picture
{
    
public:
    int w_picture;
    int h_picture;
    vector<int> vpicture;
    Picture(){};
    Picture(const char* str_file);
    void flip_picture();
    explicit Picture(vector<int> &vpicture, int w_picture, int h_picture): w_picture(w_picture), h_picture(h_picture), vpicture(vpicture) {}
    int get_pixel(int i);
    int get_pixel(int x, int y);
    void set_pixel(int x, int y, int color);
};
