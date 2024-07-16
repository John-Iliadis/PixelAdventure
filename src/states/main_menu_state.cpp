//
// Created by Gianni on 12/01/2024.
//

#include "main_menu_state.hpp"


MainMenuState::MainMenuState(StateStack &state_stack, GameContext& context, void* user_ptr)
    : State(state_stack, context)
{
    sf::Texture& bg_texture = m_context.texture_manager->get("blue");
    sf::Vector2i bg_size = static_cast<sf::Vector2i>(m_context.world_camera->get_size());

    m_scrolling_background = ScrollingBackground(bg_texture, bg_size);

    m_context.world_camera->set_center(m_context.world_camera->get_size() / 2.f);

    MusicPlayer::play("menu_music", true);

    gui_sprite.set_texture(m_context.texture_manager->get("large_button"));
    gui_sprite.move(20, 20);
    gui_sprite.scale(4, 4);
}

void MainMenuState::on_exit()
{
    State::on_exit();

}

void MainMenuState::on_return()
{
    State::on_return();

}

bool MainMenuState::handle_events(const sf::Event &event)
{

    return false;
}

bool MainMenuState::update(double dt)
{
    m_scrolling_background.update(dt);

    return false;
}

void MainMenuState::on_world_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_scrolling_background);
}

void MainMenuState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    gui_sprite.draw(window);
}

void MainMenuState::play_callback()
{
    MusicPlayer::stop();
    request_stack_pop();
    request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
}

void MainMenuState::settings_callback()
{
    request_stack_push(StateID::SETTINGS);
}

void MainMenuState::exit_callback()
{
    request_stack_pop();
}
