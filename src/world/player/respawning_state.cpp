//
// Created by Gianni on 31/01/2024.
//

#include "respawning_state.hpp"
#include "player.hpp"

RespawningState::RespawningState(Player &player)
{
    player.set_position(player.get_respawn_pos().x, player.get_respawn_pos().y - 16);
    player.set_velocity(0, 0);
    player.set_gravity(false);
    player.set_animation("respawning");
    player.set_origin(Origin::CENTER);
}

PlayerState* RespawningState::update(Player &player)
{
    if (player.animation_finished())
    {
        player.set_origin(Origin::CENTER_BOTTOM);
        player.set_alive(true);
        player.set_gravity(true);
        player.set_position(player.get_respawn_pos());
        return new IdleState(player);
    }

    return nullptr;
}
