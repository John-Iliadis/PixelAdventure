//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_MENU_STATE_HPP
#define PLATFORMER_MENU_STATE_HPP

#include "state.hpp"

class MenuState : public State
{
public:
    MenuState(StateStack& state_stack, GameContext& context, UINT_PTR user_ptr = 0);

    bool handle_events(const sf::Event &event) override;

    bool update(double dt) override;

    void draw() override;
};


#endif //PLATFORMER_MENU_STATE_HPP
