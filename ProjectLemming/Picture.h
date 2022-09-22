#pragma once
#include <vector>

using namespace std;

class Picture
{
private:
    //CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH]
    
public:
    int w_picture;
    int h_picture;
    vector<int> vpicture;
    Picture(const char* str_file);
    explicit Picture(vector<int> vpicture, int w_picture, int h_picture): w_picture(w_picture), h_picture(h_picture), vpicture(vpicture) {}
    int GetPixel(int x, int y);
};
