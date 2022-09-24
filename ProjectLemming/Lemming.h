#pragma once
#include "Animation.h"

enum State
{
    RMOVE = 0, LMOVE = 1, FALL = 2, DIG = 3
};

struct Movement
{
    State state;
    COORD lem_vector;
};

class Lemming
{
public:
    vector<Animation*> animations;
    Movement movements[4] = {{RMOVE, {1, 0}}, {LMOVE, {-1, 0}}, {FALL, {0, 1}}, {DIG, {0, 1}}};
    COORD POS;
    State currant_state = RMOVE;
    int next_frame_to_play = 0;
    Lemming(vector<Animation*> animation, COORD POS) : animations(animation), POS(POS){}
    void play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer);
    void change_state(State newState);
    State get_state();
    COORD get_center();
};
