//
// Created by Gianni on 12/01/2024.
//

#include "state.hpp"
#include "state_stack.hpp"


State::State(StateStack& state_stack, GameContext& context)
    : m_state_stack(state_stack)
    , m_context(context)
    , m_status(Status::CURRENT)
{
}

void State::on_exit()
{
    m_status = Status::OBSCURED;
}

void State::on_return()
{
    m_status = Status::CURRENT;
}

void State::request_stack_push(StateID state_id)
{
    m_state_stack.push(state_id);
}

void State::request_stack_pop()
{
    m_state_stack.pop();
}

void State::request_stack_clear()
{
    m_state_stack.clear();
}
