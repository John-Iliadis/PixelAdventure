//
// Created by Gianni on 13/02/2024.
//

#include "loading_state.hpp"

LoadingState::LoadingState(StateStack &state_stack, GameContext &context, void *user_ptr)
    : State(state_stack, context)
{

}

bool LoadingState::handle_events(const sf::Event &event)
{
    return false;
}

bool LoadingState::update(double dt)
{
    return false;
}

void LoadingState::on_world_draw()
{

}

void LoadingState::on_gui_draw()
{

}
