//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_DOUBLE_JUMPING_STATE_HPP
#define PLATFORMER_DOUBLE_JUMPING_STATE_HPP

#include "player_state.hpp"


class DoubleJumpingState : public PlayerState
{
public:
    DoubleJumpingState(Player& player);

    PlayerState* handle_event(Player &player, const sf::Event &event) override;
    PlayerState* update(Player &player, double dt) override;
};


#endif //PLATFORMER_DOUBLE_JUMPING_STATE_HPP
