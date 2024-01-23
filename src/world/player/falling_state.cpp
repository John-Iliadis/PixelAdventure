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

PlayerState* FallingState::handle_event(Player &player, const sf::Event &event)
{
    auto& data = player.get_platformer_data();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        if (!data.previously_jumped)
            return new JumpingState(player);

        if (!data.previously_double_jumped)
            return new DoubleJumpingState(player);
    }

    return nullptr;
}

PlayerState* FallingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y == 0)
    {
        if (data.velocity.x != 0)
            return new RunningState(player);

        return new IdleState(player);
    }

    if (data.touching_wall)
        return new WallSlidingState(player);

    return nullptr;
}
