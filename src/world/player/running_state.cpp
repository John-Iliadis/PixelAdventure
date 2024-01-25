//
// Created by Gianni on 18/01/2024.
//

#include "running_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"
#include "idle_state.hpp"


RunningState::RunningState(Player &player)
{
    player.set_animation("running");
    player.set_previously_jumped(false);
    player.set_previously_double_jumped(false);
}

PlayerState* RunningState::update(Player &player)
{
    if (player.get_jump_pressed_ellapsed_time() > 0)
        return new JumpingState(player);

    if (player.get_velocity().y > 0)
        return new FallingState(player);

    if (player.get_velocity().x == 0)
        return new IdleState(player);

    return nullptr;
}
