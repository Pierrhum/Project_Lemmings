#pragma once
#include "Animation.h"

enum State
{
    RMOVE = 0, LMOVE = 1, FALL = 2, DIG = 3, END = 4
};

enum SIDES {TOP, BOTTOM, LEFT, RIGHT};

struct Movement
{
    State state;
    COORD lem_vector;
};

class Lemming
{
public:
    vector<Animation*> animations;
    Movement movements[5] = {{RMOVE, {1, 0}}, {LMOVE, {-1, 0}}, {FALL, {0, 1}}, {DIG, {0, 1}}, {END, {0, 0}}};
    COORD SIZE;
    COORD POS;
    State currant_state;
    int next_frame_to_play = 0;
    Lemming(vector<Animation*> animation, COORD POS, State currant_state = RMOVE) : animations(animation), POS(POS), currant_state(currant_state){}
    
    void Update(std::vector<std::vector<CHAR_INFO>> &buffer);
    bool isColliding(SIDES side) const;
    void play_next_frame(std::vector<std::vector<CHAR_INFO>> &buffer);
    void change_state(State newState);
    State get_state();
    COORD get_center();
};
