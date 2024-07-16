//
// Created by Gianni on 10/02/2024.
//

#include "game_over_state.hpp"


GameOverState::GameOverState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
    sf::Vector2f gui_camera_pos = m_context.gui_camera->get_center();
    m_context.gui_camera->set_center(gui_camera_pos.x, gui_camera_pos.y + 1000);
    m_context.gui_camera->set_target(gui_camera_pos, easing_functions::linear);
}

bool GameOverState::handle_events(const sf::Event &event)
{

    return false;
}

bool GameOverState::update(double dt)
{

    return true;
}

void GameOverState::on_world_draw()
{

}

void GameOverState::on_gui_draw()
{
}

void GameOverState::restart_callback()
{
//    m_gui_container.deselect_all();
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
}

void GameOverState::main_menu_callback()
{
//    m_gui_container.deselect_all();

    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new DoNothing(StateID::MAIN_MENU));
}

void GameOverState::exit_callback()
{
    request_stack_clear();
}
