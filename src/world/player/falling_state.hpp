//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_FALLING_STATE_HPP
#define PLATFORMER_FALLING_STATE_HPP

#include "player_state.hpp"
#include "../../utilities/utils.hpp"


class FallingState : public PlayerState
{
public:
    FallingState(Player& player);

    PlayerState *handle_event(Player &player, const sf::Event &event) override;
    PlayerState *update(Player &player, double dt) override;

private:
    bool last_direction;
};


#endif //PLATFORMER_FALLING_STATE_HPP