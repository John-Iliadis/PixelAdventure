//
// Created by Gianni on 18/01/2024.
//

#include <iostream>
#include "running_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"
#include "idle_state.hpp"


RunningState::RunningState(Player &player)
{
    auto data = player.get_platformer_data();

    running_animation = LoopingAnimation(32, 32, 12, sf::milliseconds(50));
    player.set_texture("running");
    player.set_texture_rect(static_cast<sf::IntRect>(running_animation.get_current_frame(player.facing_right())));

    data.previously_jumped = false;
    data.previously_double_jumped = false;

    puts("Running state");
}

PlayerState *RunningState::handle_event(Player &player, const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        return new JumpingState(player);

    return nullptr;
}

PlayerState *RunningState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y > 0)
        return new FallingState(player);

    if (data.velocity.x == 0)
        return new IdleState(player);

    running_animation.update();
    player.set_texture_rect(static_cast<sf::IntRect>(running_animation.get_current_frame(data.facing_right)));

    return nullptr;
}

