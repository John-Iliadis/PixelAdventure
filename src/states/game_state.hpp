//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_GAME_STATE_HPP
#define PLATFORMER_GAME_STATE_HPP

#include "state.hpp"


class GameState : public State
{
public:
    GameState(StateStack& state_stack, std::shared_ptr<GameContext> context, UINT_PTR user_ptr = 0);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void draw() override;

private:

};


#endif //PLATFORMER_GAME_STATE_HPP
