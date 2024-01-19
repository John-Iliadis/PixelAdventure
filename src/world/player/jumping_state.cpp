//
// Created by Gianni on 18/01/2024.
//

#include "jumping_state.hpp"
#include "player.hpp"
#include "falling_state.hpp"
#include "double_jumping_state.hpp"


JumpingState::JumpingState(Player &player)
{
    auto& data = player.get_platformer_data();
    data.previously_jumped = true;
    data.velocity.y = data.jump_speed;

    player.set_texture("jumping");

    last_direction = data.facing_right;

    if (!data.facing_right)
        flip_sprite_x(player.get_sprite(), data.facing_right);

    puts("Jumping state");
}

PlayerState* JumpingState::handle_event(Player &player, const sf::Event &event)
{
    auto& data = player.get_platformer_data();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        if (data.velocity.y != 0)
            return new DoubleJumpingState(player);
    }

    return nullptr;
}

PlayerState* JumpingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y >= 0)
        return new FallingState(player);

    if (data.facing_right != last_direction)
    {
        flip_sprite_x(player.get_sprite(), data.facing_right);
        last_direction = data.facing_right;
    }

    return nullptr;
}
