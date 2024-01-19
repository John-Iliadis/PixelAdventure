//
// Created by Gianni on 18/01/2024.
//

#include "idle_state.hpp"
#include "player.hpp"
#include "running_state.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"


void IdleState::on_enter(Player &player)
{
    idle_animation = LoopingAnimation(32, 32, 11, sf::milliseconds(50), true);
    player.set_texture("idle");
    player.set_texture_rect(static_cast<sf::IntRect>(idle_animation.get_current_frame(player.facing_right())));
    player.get_platformer_data().previously_jumped = false;
    player.get_platformer_data().previously_double_jumped = false;
}

void IdleState::on_exit(Player &player)
{
}

PlayerState* IdleState::handle_event(Player &player, const sf::Event &event)
{
    auto data = player.get_platformer_data();

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up && !data.collide_directions[PlatformerData::UP] && !data.previously_jumped)
            return new JumpingState();
    }

    return nullptr;
}

PlayerState* IdleState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y > 0)
        return new FallingState();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // do nothing
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        data.facing_right = false;
        return new RunningState();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        data.facing_right = true;
        return new RunningState();
    }

    idle_animation.update();
    player.set_texture_rect(static_cast<sf::IntRect>(idle_animation.get_current_frame(data.facing_right)));
    return nullptr;
}
