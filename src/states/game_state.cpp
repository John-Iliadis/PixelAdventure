//
// Created by Gianni on 13/01/2024.
//

#include "game_state.hpp"


GameState::GameState(StateStack &state_stack, GameContext& context, void* user_ptr)
    : State(state_stack, context)
    , world(context, *reinterpret_cast<LevelDetails*>(user_ptr))
{
    delete reinterpret_cast<LevelDetails*>(user_ptr);
}

bool GameState::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            request_stack_push(StateID::PAUSE);
        }
    }

    world.handle_events(event);

    return false;
}

bool GameState::update(double dt)
{
    world.update(dt);

    return false;
}

void GameState::on_world_draw()
{
    world.draw();
}

void GameState::on_gui_draw()
{
}
