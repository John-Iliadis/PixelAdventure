//
// Created by Gianni on 13/01/2024.
//

#include "game_state.hpp"


GameState::GameState(StateStack &state_stack, GameContext& context, void* user_ptr)
    : State(state_stack, context)
    , m_world(reinterpret_cast<World*>(user_ptr))
{
    MusicPlayer::play("world_music_2", true);
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

    m_world->handle_events(event);

    return false;
}

bool GameState::update(double dt)
{
    m_world->update(dt);

    if (m_world->game_over() && m_status == Status::CURRENT)
    {
        request_stack_push(StateID::GAME_OVER);
    }

    return false;
}

void GameState::on_world_draw()
{
    m_world->draw();
}

void GameState::on_gui_draw()
{
}
