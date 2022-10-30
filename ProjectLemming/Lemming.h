#pragma once

#include <vector>
#include <windows.h>
#include "Animation.h"
#include "Element.h"


enum State
{
    RMOVE = 0, LMOVE = 1, FALL = 2, DIG = 3, END = 4, BOOM = 5, CRASH = 6, UMBRELLA = 7, WAIT = 8, DEAD = 9
};

enum SIDES {TOP, BOTTOM, LEFT, RIGHT};

/**
 * \brief Movements associated to each frame
 */
struct Movement
{
    State state;
    vector<COORD> lem_vector_list;
};

/**
 * \brief A Lemming is an Element that can collide to the current level, and has a simple AI (yeah they're dumb) that is updated each frame
 */
class Lemming : public Element
{
private:
    // distance travelled since the Lemming fell
    int fallDistance = 0;
public:
    State current_state;
    Movement movements[9] = {
        {RMOVE, {{1, 0}}},
        {LMOVE, {{-1, 0}}},
        {FALL, {{0, 1}}},
        {DIG, {{0, 0}, {0, 0}, {0, 0}, {0, 1}}},
        {END, {{0, 0}, {0, 0}, {0, -1}, {0, -1}, {0, 0}, {0, -1}, {0, 0}, {0, 0}}},
        {BOOM, {{0, 0}}},
        {CRASH, {{0, 0}}},
        {UMBRELLA, {{0, 0}, {1, 1}, {0, 0}, {-1, 1}, {0, 0}, {-1, 1}, {0, 0}, {1, 1}}},
        {WAIT, {{0, 0}}},
    };
    bool is_showed = false;
    bool is_umbrellaed = false;
    
    Lemming(vector<Animation*> animation, COORD POS, State current_state = RMOVE) :
        Element(animation, POS, true), current_state(current_state)
    {
        Picture pic = animations.at(current_state)->origin_picture;
        SIZE.X = (short)pic.w_picture;
        SIZE.Y = (short)pic.h_picture/animations.at(current_state)->nb_frames;

        // Set to true to debug the Lemming collider
        debugOutline = false;
    }

    /**
     * \brief Update the Lemming state
     * \param buffer : buffer containing every pixels
     */
    void Update(std::vector<std::vector<CHAR_INFO>> &buffer);

    /**
     * \brief Dig the line under the lemming, and update the current level pixels
     */
    void Dig();

    /**
     * \brief Check if the Lemming is colliding with the level, or with a waiting Lemming
     * \param side : Analysed Side
     * \return true if colliding
     */
    bool isColliding(SIDES side) const;

    /**
     * \brief Check if it is possible to climb on the map
     * \param side  : Analysed Side (LEFT or RIGHT only)
     * \return true if it is possible to climb 
     */
    bool canClimb(SIDES side) const;

    /**
     * \brief Set the lemming state, and manage the change
     * \param state : New lemming state
     */
    void SetState(State state);

private:
    State fall_state = RMOVE; // State avant la chute (pour récupérer la bonne direction une fois tombé)
};
