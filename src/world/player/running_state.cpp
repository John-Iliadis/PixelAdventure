//
// Created by Gianni on 18/01/2024.
//

#include <iostream>
#include "running_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"

void RunningState::on_enter(Player &player)
{
    auto data = player.get_platformer_data();

    running_animation = LoopingAnimation(32, 32, 12, sf::milliseconds(50));
    player.set_texture("running");
    player.set_texture_rect(static_cast<sf::IntRect>(running_animation.get_current_frame(player.facing_right())));

    // todo: check this
    if (player.facing_right())
        data.velocity.x = data.move_speed;
    else
        data.velocity.x = -data.move_speed;

    data.previously_jumped = false;
    data.previously_double_jumped = false;
}

void RunningState::on_exit(Player &player)
{
}

PlayerState *RunningState::handle_event(Player &player, const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        return new JumpingState();
    }

    return nullptr;
}

PlayerState *RunningState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y > 0)
        return new FallingState();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    {
        return new IdleState();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.get_platformer_data().velocity.x = -player.get_platformer_data().move_speed;
        data.facing_right = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.get_platformer_data().velocity.x = player.get_platformer_data().move_speed;
        data.facing_right = true;
    }

    running_animation.update();
    player.set_texture_rect(static_cast<sf::IntRect>(running_animation.get_current_frame(data.facing_right)));
    return nullptr;
}
