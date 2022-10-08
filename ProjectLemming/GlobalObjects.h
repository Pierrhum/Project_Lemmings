#pragma once

#include <vector>

#include "Element.h"
#include "Lemming.h"
#include "Animation.h"

class GlobalObjects
{
public:
    GlobalObjects(): drop(new Animation("spriteAscii/drop/drop16.txt", 10), COORD{50, 20}, false), door(new Animation("spriteAscii/door/door16.txt", 6), COORD{145, 67}, true)
    {
        _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8));
        _anims.push_back( new Animation("spriteAscii/lemming_move/lem_move_size8.txt", 8, true));
        _anims.push_back( new Animation("spriteAscii/lemming_fall/lem_fall_size8.txt", 4));
        _anims.push_back( new Animation("spriteAscii/lemming_dig/lem_dig_size10.txt", 16));
        _anims.push_back( new Animation("spriteAscii/lemming_end/lem_end10.txt", 8));
        _anims.push_back( new Animation("spriteAscii/boom/lem_boom_size10.txt", 12));
    }

    static GlobalObjects& Instance() {
        static GlobalObjects S;
        return S;
    }
    void InitLevelOne();

    vector<Animation*> _anims;
    vector<Lemming> lemming; //for future Lemming list
    Element drop;
    Element door;
    
};
