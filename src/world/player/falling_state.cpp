//
// Created by Gianni on 18/01/2024.
//

#include "falling_state.hpp"
#include "player.hpp"
#include "running_state.hpp"
#include "jumping_state.hpp"
#include "double_jumping_state.hpp"


FallingState::FallingState(Player &player)
{
    auto& data = player.get_platformer_data();

    player.set_texture("falling");

    last_direction = data.facing_right;

    if (!data.facing_right)
        flip_sprite_x(player.get_sprite(), data.facing_right);

    puts("Falling state");
}

PlayerState* FallingState::handle_event(Player &player, const sf::Event &event)
{
    auto& data = player.get_platformer_data();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        if (!data.previously_jumped)
            return new JumpingState(player);

//        if (!data.previously_double_jumped)
//            return new DoubleJumpingState();
    }

    return nullptr;
}

PlayerState* FallingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y == 0)
    {
        if (data.velocity != sf::Vector2f(0, 0))
            return new RunningState(player);

        return new IdleState(player);
    }

    if (data.facing_right != last_direction)
    {
        flip_sprite_x(player.get_sprite(), data.facing_right);
        last_direction = data.facing_right;
    }

    return nullptr;
}
