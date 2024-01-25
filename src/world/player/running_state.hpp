//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_RUNNING_STATE_HPP
#define PLATFORMER_RUNNING_STATE_HPP

#include "player_state.hpp"


class RunningState : public PlayerState
{
public:
    RunningState(Player& player);
    PlayerState* update(Player &player) override;
};


#endif //PLATFORMER_RUNNING_STATE_HPP
