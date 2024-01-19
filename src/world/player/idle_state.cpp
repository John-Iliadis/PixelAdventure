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

    idle_animation = LoopingAnimation(32, 32, 11, sf::milliseconds(50), true);

    player.set_texture("idle");
    player.set_texture_rect(static_cast<sf::IntRect>(idle_animation.get_current_frame(player.facing_right())));

    data.previously_jumped = false;
    data.previously_double_jumped = false;
}

PlayerState* IdleState::handle_event(Player &player, const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
            return new JumpingState(player);
    }

    return nullptr;
}

PlayerState* IdleState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y > 0)
        return new FallingState(player);

    if (data.velocity.x != 0)
        return new RunningState(player);

    idle_animation.update();
    player.set_texture_rect(static_cast<sf::IntRect>(idle_animation.get_current_frame(data.facing_right)));

    return nullptr;
}
