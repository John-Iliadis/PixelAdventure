//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_RUNNING_STATE_HPP
#define PLATFORMER_RUNNING_STATE_HPP

#include "../../animation/looping_animation.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "player_state.hpp"


class RunningState : public PlayerState
{
public:
    void on_enter(Player &player) override;
    void on_exit(Player &player) override;

    PlayerState *handle_event(Player &player, const sf::Event &event) override;
    PlayerState *update(Player &player, double dt) override;

private:
    LoopingAnimation running_animation;
};


#endif //PLATFORMER_RUNNING_STATE_HPP
