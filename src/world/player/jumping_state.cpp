//
// Created by Gianni on 18/01/2024.
//

#include "jumping_state.hpp"
#include "player.hpp"
#include "falling_state.hpp"
#include "double_jumping_state.hpp"

void JumpingState::on_enter(Player &player)
{
    auto& data = player.get_platformer_data();
    data.previously_jumped = true;
    data.velocity.y = data.jump_speed;

    player.set_texture("jumping");

    if (!data.facing_right)
        flip_sprite_x(player.get_sprite(), data.facing_right);
}

void JumpingState::on_exit(Player &player)
{
}

PlayerState *JumpingState::handle_event(Player &player, const sf::Event &event)
{
    auto& data = player.get_platformer_data();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        if (data.velocity.y != 0)
            return new DoubleJumpingState();
    }

    return nullptr;
}

PlayerState* JumpingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.get_platformer_data().velocity.x = -player.get_platformer_data().move_speed;

        if (data.facing_right)
        {
            data.facing_right = false;
            flip_sprite_x(player.get_sprite(), data.facing_right);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.get_platformer_data().velocity.x = player.get_platformer_data().move_speed;

        if (!data.facing_right)
        {
            data.facing_right = true;
            flip_sprite_x(player.get_sprite(), data.facing_right);
        }
    }

    if (data.velocity.y >= 0)
        return new FallingState();

    return nullptr;
}
