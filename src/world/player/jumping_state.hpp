//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_JUMPING_STATE_HPP
#define PLATFORMER_JUMPING_STATE_HPP

#include "player_state.hpp"
#include "../../utilities/utils.hpp"


class JumpingState : public PlayerState
{
public:
    JumpingState(Player& player);
    PlayerState* update(Player &player) override;
};


#endif //PLATFORMER_JUMPING_STATE_HPP
