//
// Created by Gianni on 18/01/2024.
//

#include "running_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"
#include "idle_state.hpp"


RunningState::RunningState(Player &player)
{
    player.set_animation("running");
    player.set_previously_jumped(false);
    player.set_previously_double_jumped(false);
}

PlayerState* RunningState::handle_event(Player &player, const sf::Event &event)
{
    return nullptr;
}

PlayerState* RunningState::update(Player &player, double dt)
{
    if (player.time_since_last_jump_button_pressed().asSeconds() <= player.get_jump_pressed_remember_time())
        return new JumpingState(player);

    if (player.get_velocity().y > 0)
        return new FallingState(player);

    if (player.get_velocity().x == 0)
        return new IdleState(player);

    return nullptr;
}
