//
// Created by Gianni on 13/01/2024.
//

#include "game_state.hpp"


GameState::GameState(StateStack &state_stack, std::shared_ptr<GameContext> context, UINT_PTR user_ptr)
    : State(state_stack, context, user_ptr)
{
}

bool GameState::handle_events(const sf::Event &event)
{
    return false;
}

bool GameState::update(double dt)
{
    return false;
}

void GameState::draw()
{

}
