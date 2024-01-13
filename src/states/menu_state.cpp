//
// Created by Gianni on 12/01/2024.
//

#include "menu_state.hpp"


MenuState::MenuState(StateStack &state_stack, GameContext& context, UINT_PTR user_ptr)
    : State(state_stack, context, user_ptr)
{
}

bool MenuState::handle_events(const sf::Event &event)
{
    return false;
}

bool MenuState::update(double dt)
{
    return false;
}

void MenuState::draw()
{

}
