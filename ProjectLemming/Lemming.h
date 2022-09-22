#pragma once
#include "Animation.h"

class Lemming
{
public:
    Animation move = Animation("spriteAscii/lem_move.txt", 8);
    // Animation fall = Animation("spriteAscii/lem_fall.txt", 8);
    Lemming();
};
