//
// Created by Gianni on 12/01/2024.
//

#include "state_factory.hpp"
#include "menu_state.hpp"
#include "game_state.hpp"


#define FACTORY_FUNCTION(T) [&] (UINT_PTR user_ptr = 0) \
    { return std::make_unique<T>(state_stack, context, user_ptr); }

StateFactory::StateFactory(StateStack& state_stack, GameContext& context)
{
    m_factory[StateID::MAIN_MENU] = FACTORY_FUNCTION(MenuState);
    m_factory[StateID::GAME] = FACTORY_FUNCTION(GameState);
}

std::unique_ptr<State> StateFactory::create_state(StateID id, UINT_PTR user_ptr)
{
    if (auto result = m_factory.find(id);
        result != m_factory.end())
    {
        return result->second(user_ptr);
    }

    throw std::runtime_error("StateFactory::create_state - State not registered\n");
}
