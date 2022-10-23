#pragma once

#include <vector>
#include <windows.h>
#include "Animation.h"


enum State
{
    RMOVE = 0, LMOVE = 1, FALL = 2, DIG = 3, END = 4, BOOM = 5
};

struct Movement
{
    State state;
    // COORD lem_vector;
    vector<COORD> lem_vector_list;
};

class Lemming
{
public:
    vector<Animation*> animations;
    // Movement movements[5] = {{RMOVE, {1, 0} }, {LMOVE, {-1, 0}}, {FALL, {0, 1}}, {DIG, {0, 1}}, {END, {0, 0}}};
    Movement movements[6] = {
        {RMOVE, {{1, 0}}},
        {LMOVE, {{-1, 0}}},
        {FALL, {{0, 1}}},
        {DIG, {{0, 0}, {0, 0}, {0, 0}, {0, 1}}},
        {END, {{0, 0}}},
        {BOOM, {{0, 0}}}};
    COORD POS;
    bool is_showed = false;
    State currant_state;
    int next_frame_to_play = 0;
    Lemming(vector<Animation*> animation, COORD POS, State currant_state = RMOVE) : animations(animation), POS(POS), currant_state(currant_state){}
    void play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer);
    void change_state(State newState);
    State get_state();
    COORD get_center();
};
