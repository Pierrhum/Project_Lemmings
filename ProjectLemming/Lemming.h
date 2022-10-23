﻿#pragma once
#include "Animation.h"
#include "Element.h"

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

class Lemming : public Element
{
public:
    Movement movements[5] = {{RMOVE, {1, 0}}, {LMOVE, {-1, 0}}, {FALL, {0, 1}}, {DIG, {0, 1}}, {END, {0, 0}}};
    State current_state;

    Lemming(vector<Animation*> animation, COORD POS, State current_state = RMOVE) :
        Element(animation, POS, true), current_state(current_state)
    {
        Picture pic = animations.at(current_state)->origin_picture;
        SIZE.X = (short)pic.w_picture;
        SIZE.Y = (short)pic.h_picture/animations.at(current_state)->nb_frames;

        // Pour débug le contour du Lemming
        debugOutline = false;
    }

    void Update(std::vector<std::vector<CHAR_INFO>> &buffer);
    void Dig();
    
    bool isColliding(SIDES side) const;
    bool canClimb(SIDES side) const;

private:
    State fall_state = RMOVE; // State avant la chute (pour récupérer la bonne direction une fois tombé
    
};
