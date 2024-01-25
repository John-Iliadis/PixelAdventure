//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_IDLE_STATE_HPP
#define PLATFORMER_IDLE_STATE_HPP

#include "player_state.hpp"


class IdleState : public PlayerState
{
public:
    IdleState(Player& player);
    PlayerState* update(Player &player) override;
};


#endif //PLATFORMER_IDLE_STATE_HPP
