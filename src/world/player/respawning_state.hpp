//
// Created by Gianni on 31/01/2024.
//

#ifndef PLATFORMER_RESPAWNING_STATE_HPP
#define PLATFORMER_RESPAWNING_STATE_HPP

#include "../../audio/sound_player.hpp"
#include "player_state.hpp"

class RespawningState : public PlayerState
{
public:
    RespawningState(Player& player);
    PlayerState* update(Player& player) override;
};


#endif //PLATFORMER_RESPAWNING_STATE_HPP
