//
// Created by Gianni on 12/01/2024.
//

#include "state_factory.hpp"
#include "main_menu_state.hpp"
#include "game_state.hpp"
#include "settings_state.hpp"
#include "pause_state.hpp"
#include "game_over_state.hpp"
#include "key_binding_state.hpp"


#define FACTORY_FUNCTION(STATE_TYPE) [&] (UINT_PTR user_ptr = 0)                                                       \
    {                                                                                                                  \
        if constexpr (!std::is_base_of<State, STATE_TYPE>::value) __debugbreak();                                      \
        return std::make_unique<STATE_TYPE>(state_stack, context, user_ptr);                                           \
    }

StateFactory::StateFactory(StateStack& state_stack, GameContext& context)
{
    m_factory[StateID::MAIN_MENU] = FACTORY_FUNCTION(MainMenuState);
    m_factory[StateID::GAME] = FACTORY_FUNCTION(GameState);
    m_factory[StateID::SETTINGS] = FACTORY_FUNCTION(SettingsState);
    m_factory[StateID::PAUSE] = FACTORY_FUNCTION(PauseState);
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
