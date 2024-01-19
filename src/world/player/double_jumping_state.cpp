//
// Created by Gianni on 18/01/2024.
//

#include "player.hpp"
#include "double_jumping_state.hpp"
#include "falling_state.hpp"


void DoubleJumpingState::on_enter(Player &player)
{
    auto& data = player.get_platformer_data();

    double_jump_anim = NonLoopingAnimation(32, 32, 6, sf::milliseconds(50), true);

    player.set_texture("double_jumping");
    player.set_texture_rect(static_cast<sf::IntRect>(double_jump_anim.get_current_frame(data.facing_right)));

    data.previously_double_jumped = true;
    data.velocity.y = data.jump_speed;
}

void DoubleJumpingState::on_exit(Player &player)
{
}

PlayerState *DoubleJumpingState::handle_event(Player &player, const sf::Event &event)
{
    return nullptr;
}

PlayerState *DoubleJumpingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

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

    if (data.velocity.y > 0)
        return new FallingState();

    double_jump_anim.update();
    player.set_texture_rect(static_cast<sf::IntRect>(double_jump_anim.get_current_frame(data.facing_right)));
    return nullptr;
}
