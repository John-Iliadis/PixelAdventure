//
// Created by Gianni on 18/01/2024.
//

#include "wall_sliding_state.hpp"
#include "player.hpp"
#include "jumping_state.hpp"
#include "falling_state.hpp"


WallSlidingState::WallSlidingState(Player &player)
{
    player.set_animation("wall_sliding");
    player.set_gravity(false);
    player.set_previously_jumped(false);
    player.set_previously_double_jumped(false);
    player.set_velocity(player.get_velocity().x, player.get_wall_sliding_speed());
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

    if (player.get_velocity().y == 0)
    {
        player.set_gravity(true);
        return new IdleState(player);
    }

    if (!player.touching_wall())
    {
        player.set_gravity(true);
        return new FallingState(player);
    }

    return nullptr;
}
