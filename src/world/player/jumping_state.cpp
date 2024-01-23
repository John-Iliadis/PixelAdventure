//
// Created by Gianni on 18/01/2024.
//

#include "jumping_state.hpp"
#include "player.hpp"
#include "falling_state.hpp"
#include "double_jumping_state.hpp"


JumpingState::JumpingState(Player &player)
{
    player.set_animation("jumping");
    player.set_previously_jumped(true);
    player.jump();
}

PlayerState* JumpingState::handle_event(Player &player, const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        return new DoubleJumpingState(player);

    return nullptr;
}

PlayerState* JumpingState::update(Player &player, double dt)
{
    if (player.get_velocity().y >= 0)
        return new FallingState(player);

    return nullptr;
}
