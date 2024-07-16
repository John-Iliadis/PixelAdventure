//
// Created by Gianni on 10/02/2024.
//

#include "settings_state.hpp"


SettingsState::SettingsState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
}

void SettingsState::on_return()
{
    State::on_return();
}

bool SettingsState::handle_events(const sf::Event &event)
{
    return false;
}

bool SettingsState::update(double dt)
{
    return true;
}

void SettingsState::on_world_draw()
{
}

void SettingsState::on_gui_draw()
{
}

void SettingsState::left_binding_callback()
{
    std::string* action = new std::string("move_left_action");

    auto action_ptr = reinterpret_cast<void*>(action);

    request_stack_push(StateID::KEY_BINDING, action_ptr);
}

void SettingsState::right_binding_callback()
{
    std::string* action = new std::string("move_right_action");

    auto action_ptr = reinterpret_cast<void*>(action);

    request_stack_push(StateID::KEY_BINDING, action_ptr);
}

void SettingsState::up_binding_callback()
{
    std::string* action = new std::string("jump_action");

    auto action_ptr = reinterpret_cast<void*>(action);

    request_stack_push(StateID::KEY_BINDING, action_ptr);
}

void SettingsState::back_callback()
{
    request_stack_pop();
}
