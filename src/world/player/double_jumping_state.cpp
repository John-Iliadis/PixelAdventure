//
// Created by Gianni on 18/01/2024.
//

#include "player.hpp"
#include "double_jumping_state.hpp"
#include "falling_state.hpp"


DoubleJumpingState::DoubleJumpingState(Player &player)
{
    auto& data = player.get_platformer_data();

    player.set_animation("double_jumping");

    data.previously_double_jumped = true;
    data.velocity.y = data.jump_speed;
}

PlayerState* DoubleJumpingState::handle_event(Player &player, const sf::Event &event)
{
    return nullptr;
}

PlayerState* DoubleJumpingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y > 0)
        return new FallingState(player);

    return nullptr;
}
