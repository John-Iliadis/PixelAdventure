//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_WALL_SLIDING_STATE_HPP
#define PLATFORMER_WALL_SLIDING_STATE_HPP

#include "player_state.hpp"


class WallSlidingState : public PlayerState
{
public:
    WallSlidingState(Player& player);

    PlayerState* handle_event(Player &player, const sf::Event &event) override;
    PlayerState* update(Player &player, double dt) override;
};


#endif //PLATFORMER_WALL_SLIDING_STATE_HPP
