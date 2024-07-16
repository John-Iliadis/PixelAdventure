//
// Created by Gianni on 10/02/2024.
//

#include "pause_state.hpp"


PauseState::PauseState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
    m_dark_overlay.setSize(static_cast<sf::Vector2f>(m_context.window->getSize()));
    m_dark_overlay.setFillColor(sf::Color(0, 0, 0, 128));

    SoundPlayer::play_sound("window_open");
}

void PauseState::on_exit()
{
    State::on_exit();
}

void PauseState::on_return()
{
    State::on_return();
}

bool PauseState::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            request_stack_pop();
        }
    }

    return false;
}

bool PauseState::update(double dt)
{


    return false;
}

void PauseState::on_world_draw()
{
}

void PauseState::on_gui_draw()
{
    sf::RenderWindow &window = *m_context.window;

    window.draw(m_dark_overlay);
}

void PauseState::play_callback()
{
    request_stack_pop();
}

void PauseState::restart_callback()
{
//    m_gui_container.deselect_all();
    MusicPlayer::stop();
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
}

void PauseState::settings_callback()
{
    request_stack_push(StateID::SETTINGS);
}

void PauseState::menu_callback()
{
//    m_gui_container.deselect_all();
    MusicPlayer::stop();
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new DoNothing(StateID::MAIN_MENU));
}

void PauseState::desktop_callback()
{
    request_stack_clear(); // todo: instead of window.close
}
