//
// Created by Gianni on 18/01/2024.
//

#include "wall_sliding_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"


WallSlidingState::WallSlidingState(Player &player)
{
    player.set_animation("wall_sliding");
    player.set_gravity(false);
    player.set_previously_jumped(false);
    player.set_previously_double_jumped(false);
    player.set_velocity(player.get_velocity().x, player.get_wall_sliding_speed());
}

PlayerState* WallSlidingState::update(Player &player)
{
    PlayerState* new_state = nullptr;

    if (player.get_jump_pressed_ellapsed_time() > 0)
    {
        new_state = new JumpingState(player);
    }
    else if (player.get_velocity().y == 0)
    {
        new_state = new IdleState(player);
    }
    else if (!player.touching_wall())
    {
        new_state = new FallingState(player);
    }

    if (new_state)
        player.set_gravity(true);

    return new_state;
}
