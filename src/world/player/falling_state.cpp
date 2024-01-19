//
// Created by Gianni on 18/01/2024.
//

#include "falling_state.hpp"
#include "player.hpp"
#include "running_state.hpp"
#include "jumping_state.hpp"
#include "double_jumping_state.hpp"


void FallingState::on_enter(Player &player)
{
    auto& data = player.get_platformer_data();

    player.set_texture("falling");

    if (!data.facing_right)
        flip_sprite_x(player.get_sprite(), data.facing_right);
}

void FallingState::on_exit(Player &player)
{
}

PlayerState* FallingState::handle_event(Player &player, const sf::Event &event)
{
    auto& data = player.get_platformer_data();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        if (!data.previously_jumped)
            return new JumpingState();

        if (!data.previously_double_jumped)
            return new DoubleJumpingState();
    }

    return nullptr;
}

PlayerState *FallingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.get_platformer_data().velocity.x = -player.get_platformer_data().move_speed;

        if (data.facing_right)
        {
            data.facing_right = false;
            flip_sprite_x(player.get_sprite(), data.facing_right);
        }

        moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.get_platformer_data().velocity.x = player.get_platformer_data().move_speed;

        if (!data.facing_right)
        {
            data.facing_right = true;
            flip_sprite_x(player.get_sprite(), data.facing_right);
        }

        moving = true;
    }

    if (data.velocity.y == 0)
    {
        if (moving)
            return new RunningState();

        return new IdleState();
    }

    return nullptr;
}
