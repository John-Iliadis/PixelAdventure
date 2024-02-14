//
// Created by Gianni on 18/01/2024.
//

#include "jumping_state.hpp"
#include "player.hpp"
#include "falling_state.hpp"
#include "double_jumping_state.hpp"


JumpingState::JumpingState(Player &player)
{
    player.set_animation("jumping");
    player.set_previously_jumped(true);
    player.jump();

    SoundPlayer::play_sound("jump");
}

PlayerState* JumpingState::update(Player &player)
{
    if (player.get_jump_pressed_ellapsed_time() > 0)
        return new DoubleJumpingState(player);

    if (player.get_velocity().y >= 0)
        return new FallingState(player);

    return nullptr;
}
