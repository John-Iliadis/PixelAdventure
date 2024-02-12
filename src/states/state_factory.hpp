//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_STATE_FACTORY_HPP
#define PLATFORMER_STATE_FACTORY_HPP

#include <unordered_map>
#include <functional>
#include <memory>
#include <basetsd.h>
#include "../enums/state_identifiers.hpp"
#include "game_context.hpp"
#include "../utilities/utils.hpp"


class State;
class StateStack;

class StateFactory
{
public:
    StateFactory() = default;
    StateFactory(StateStack& state_stack, GameContext& context);

    std::unique_ptr<State> create_state(StateID id, void* user_ptr = nullptr);

private:
    std::unordered_map<StateID, std::function<std::unique_ptr<State>(void*)>> m_factory;
};


#endif //PLATFORMER_STATE_FACTORY_HPP
