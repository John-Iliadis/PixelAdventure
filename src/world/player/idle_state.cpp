//
// Created by Gianni on 18/01/2024.
//

#include "idle_state.hpp"
#include "player.hpp"
#include "running_state.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"


IdleState::IdleState(Player &player)
{
    player.set_animation("idle");
    player.set_previously_jumped(false);
    player.set_previously_double_jumped(false);
}

PlayerState* IdleState::update(Player &player)
{
    if (player.get_jump_pressed_ellapsed_time() > 0)
        return new JumpingState(player);

    if (player.get_velocity().y > 0)
        return new FallingState(player);

    if (player.get_velocity().x != 0)
        return new RunningState(player);

    return nullptr;
}
