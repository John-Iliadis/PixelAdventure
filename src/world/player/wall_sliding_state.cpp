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

    sliding_anim = LoopingAnimation(32, 32, 5, sf::milliseconds(50), true);

    player.set_texture("wall_sliding");
    player.set_texture_rect(static_cast<sf::IntRect>(sliding_anim.get_current_frame(data.facing_right)));

    data.previously_jumped = false;
    data.previously_double_jumped = false;

    player.set_gravity(false);

    data.velocity.y = data.wall_sliding_speed;

    facing_right = data.facing_right;
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

    if (facing_right != data.facing_right)
    {
        player.set_gravity(true);
        return new FallingState(player);
    }

    sliding_anim.update();
    player.set_texture_rect(static_cast<sf::IntRect>(sliding_anim.get_current_frame(data.facing_right)));

    return nullptr;
}
