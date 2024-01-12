//
// Created by Gianni on 12/01/2024.
//

#include "state_factory.hpp"
#include "test_state.hpp"


StateFactory::StateFactory(StateStack *state_stack, std::shared_ptr<GameContext> context)
    : m_state_stack(state_stack)
    , m_context(context)
{
}

std::unique_ptr<State> StateFactory::create_state(StateID id, UINT_PTR user_ptr)
{
    return m_factory[id](user_ptr);
}
