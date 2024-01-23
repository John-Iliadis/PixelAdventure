//
// Created by Gianni on 18/01/2024.
//

#include "wall_sliding_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"


WallSlidingState::WallSlidingState(Player &player)
{
    auto& data = player.get_platformer_data();

    player.set_animation("wall_sliding");
    player.set_gravity(false);

    data.previously_jumped = false;
    data.previously_double_jumped = false;
    data.velocity.y = data.wall_sliding_speed;
}

PlayerState* WallSlidingState::handle_event(Player &player, const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
    {
        player.set_gravity(true);
        return new JumpingState(player);
    }

    return nullptr;
}

PlayerState* WallSlidingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();


    if (data.velocity.y == 0)
    {
        player.set_gravity(true);
        return new IdleState(player);
    }

    if (!data.touching_wall)
    {
        player.set_gravity(true);
        return new FallingState(player);
    }

    return nullptr;
}
