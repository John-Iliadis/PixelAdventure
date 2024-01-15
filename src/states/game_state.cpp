//
// Created by Gianni on 13/01/2024.
//

#include "game_state.hpp"


GameState::GameState(StateStack &state_stack, GameContext& context, UINT_PTR user_ptr)
    : State(state_stack, context, user_ptr)
    , world(context)
{
}

bool GameState::handle_events(const sf::Event &event)
{
    world.handle_events(event);
    return false;
}

bool GameState::update(double dt)
{
    world.update(dt);
    return false;
}

void GameState::draw()
{
    world.draw();
}
