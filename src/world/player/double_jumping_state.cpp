//
// Created by Gianni on 18/01/2024.
//

#include "player.hpp"
#include "double_jumping_state.hpp"
#include "falling_state.hpp"


DoubleJumpingState::DoubleJumpingState(Player &player)
{
    player.set_animation("double_jumping");
    player.set_previously_double_jumped(true);
    player.jump();
    SoundPlayer::play_sound("double_jump");
}

PlayerState* DoubleJumpingState::update(Player &player)
{
    if (player.get_velocity().y > 0)
        return new FallingState(player);

    return nullptr;
}
