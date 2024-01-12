//
// Created by Gianni on 12/01/2024.
//

#include "state_stack.hpp"
#include "state.hpp"


StateStack::StateStack(std::shared_ptr<GameContext> context)
    : m_state_factory(this, context)
{
}

void StateStack::handle_events(const sf::Event &event)
{
    for (auto& state : std::ranges::views::reverse(m_state_stack))
    {
        if (!state->handle_events(event))
            break;
    }

    apply_pending_changes();
}

void StateStack::update(double dt)
{
    for (auto& state : std::ranges::views::reverse(m_state_stack))
    {
        if (!state->update(dt))
            break;
    }

    apply_pending_changes();
}

void StateStack::draw()
{
    for (auto& state : m_state_stack)
        state->draw();
}

void StateStack::push(StateID id, UINT_PTR user_ptr)
{
    m_pending_changes.emplace_back(Action::PUSH, id, user_ptr);
}

void StateStack::pop()
{
    m_pending_changes.emplace_back(Action::POP);
}

void StateStack::clear()
{
    m_pending_changes.emplace_back(Action::CLEAR);
}

void StateStack::apply_pending_changes()
{
    for (const auto& [action, id, user_ptr] : m_pending_changes)
    {
        switch (action)
        {
            case Action::PUSH:
            {
                if (!m_state_stack.empty()) m_state_stack.back()->on_exit();
                m_state_stack.push_back(m_state_factory.create_state(id, user_ptr));
                break;
            }

            case Action::POP:
            {
                m_state_stack.back()->on_exit(); // todo: might remove this. we'll see
                m_state_stack.pop_back();
                if (!m_state_stack.empty()) m_state_stack.back()->on_return();
                break;
            }

            case Action::CLEAR:
            {
                m_state_stack.clear();
                break;
            }

            case Action::NONE:
            {
                throw std::runtime_error("StateStack::apply_pending_changes - Action is set to NONE\n");
            }
        }
    }

    m_pending_changes.clear();
}

bool StateStack::empty() const
{
    return m_state_stack.empty();
}
