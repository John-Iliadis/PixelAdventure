//
// Created by Gianni on 18/01/2024.
//

#include "player.hpp"
#include "double_jumping_state.hpp"
#include "falling_state.hpp"


DoubleJumpingState::DoubleJumpingState(Player &player)
{
    auto& data = player.get_platformer_data();

    double_jump_anim = NonLoopingAnimation(32, 32, 6, sf::milliseconds(50), true);

    player.set_texture("double_jumping");
    player.set_texture_rect(static_cast<sf::IntRect>(double_jump_anim.get_current_frame(data.facing_right)));

    data.previously_double_jumped = true;
    data.velocity.y = data.jump_speed;

    puts("Double jumping state");
}

PlayerState *DoubleJumpingState::handle_event(Player &player, const sf::Event &event)
{
    return nullptr;
}

PlayerState *DoubleJumpingState::update(Player &player, double dt)
{
    auto& data = player.get_platformer_data();

    if (data.velocity.y > 0)
        return new FallingState(player);

    double_jump_anim.update();
    player.set_texture_rect(static_cast<sf::IntRect>(double_jump_anim.get_current_frame(data.facing_right)));

    return nullptr;
}
