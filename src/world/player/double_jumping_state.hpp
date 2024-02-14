//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_DOUBLE_JUMPING_STATE_HPP
#define PLATFORMER_DOUBLE_JUMPING_STATE_HPP

#include "../../audio/sound_player.hpp"
#include "player_state.hpp"


class DoubleJumpingState : public PlayerState
{
public:
    DoubleJumpingState(Player& player);
    PlayerState* update(Player &player) override;
};


#endif //PLATFORMER_DOUBLE_JUMPING_STATE_HPP
