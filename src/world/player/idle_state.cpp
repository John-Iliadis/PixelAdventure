//
// Created by Gianni on 18/01/2024.
//

#include "idle_state.hpp"
#include "player.hpp"
#include "running_state.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"


IdleState::IdleState(Player &player)
{
    auto& data = player.get_platformer_data();

    player.set_animation("idle");

    data.previously_jumped = false;
    data.previously_double_jumped = false;
}

PlayerState* IdleState::handle_event(Player &player, const sf::Event &event)
{
    return nullptr;
}

PlayerState* IdleState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.time_since_last_jump_button_pressed.getElapsedTime().asSeconds() <= data.jump_pressed_remember_time)
        return new JumpingState(player);

    if (data.velocity.y > 0)
        return new FallingState(player);

    if (data.velocity.x != 0)
        return new RunningState(player);

    return nullptr;
}
