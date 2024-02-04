//
// Created by Gianni on 12/01/2024.
//

#include "state.hpp"
#include "state_stack.hpp"


State::State(StateStack& state_stack, GameContext& context)
    : state_stack(state_stack)
    , context(context)
    , status(Status::CURRENT)
{
}

void State::on_exit()
{
    status = Status::OBSCURED;
}

void State::on_return()
{
    status = Status::CURRENT;
}

void State::request_stack_push(StateID state_id)
{
    state_stack.push(state_id);
}

void State::request_stack_pop()
{
    state_stack.pop();
}

void State::request_stack_clear()
{
    state_stack.clear();
}
