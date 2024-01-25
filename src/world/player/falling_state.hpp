//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_FALLING_STATE_HPP
#define PLATFORMER_FALLING_STATE_HPP

#include "player_state.hpp"


class FallingState : public PlayerState
{
public:
    FallingState(Player& player);
    PlayerState* update(Player &player) override;
};


#endif //PLATFORMER_FALLING_STATE_HPP
