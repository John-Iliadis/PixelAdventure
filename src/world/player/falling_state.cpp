//
// Created by Gianni on 18/01/2024.
//

#include "falling_state.hpp"
#include "player.hpp"
#include "running_state.hpp"
#include "jumping_state.hpp"
#include "double_jumping_state.hpp"
#include "wall_sliding_state.hpp"


FallingState::FallingState(Player &player)
{
    player.set_animation("falling");
}

PlayerState* FallingState::update(Player &player)
{
    if (player.get_jump_pressed_ellapsed_time() > 0)
    {
        if (!player.previously_jumped())
            return new JumpingState(player);

        if (!player.previously_double_jumped())
            return new DoubleJumpingState(player);
    }

    if (player.get_velocity().y == 0)
    {
        if (player.get_velocity().x != 0)
            return new RunningState(player);

        return new IdleState(player);
    }

    if (player.touching_wall())
        return new WallSlidingState(player);

    return nullptr;
}
