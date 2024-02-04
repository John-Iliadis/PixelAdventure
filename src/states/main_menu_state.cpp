//
// Created by Gianni on 12/01/2024.
//

#include "main_menu_state.hpp"


MainMenuState::MainMenuState(StateStack &state_stack, GameContext& context, UINT_PTR user_ptr)
    : State(state_stack, context)
{

}

bool MainMenuState::handle_events(const sf::Event &event)
{
    return false;
}

bool MainMenuState::update(double dt)
{
    return false;
}

void MainMenuState::draw()
{

}
