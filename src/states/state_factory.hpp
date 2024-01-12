//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_STATE_FACTORY_HPP
#define PLATFORMER_STATE_FACTORY_HPP

#include <unordered_map>
#include <functional>
#include <memory>
#include <basetsd.h>
#include "state_identifiers.hpp"
#include "game_context.hpp"


class State;
class StateStack;

class StateFactory
{
public:
    StateFactory() = default;
    StateFactory(StateStack* state_stack, std::shared_ptr<GameContext> context);

    std::unique_ptr<State> create_state(StateID id, UINT_PTR user_ptr = 0);

private:
    std::unordered_map<StateID, std::function<std::unique_ptr<State>(UINT_PTR)>> m_factory;
    std::shared_ptr<GameContext> m_context;
    StateStack* m_state_stack;
};


#endif //PLATFORMER_STATE_FACTORY_HPP
