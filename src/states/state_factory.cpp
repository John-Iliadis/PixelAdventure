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
#include "pre_game_loading_state.hpp"


#define FACTORY_FUNCTION(STATE_TYPE) [&] (void* user_ptr = nullptr)                                   \
    {                                                                                                 \
        static_assert(std::is_base_of<State, STATE_TYPE>::value,                                      \
                      "StateFactory::StateFactory: STATE_TYPE not derived from State class");         \
                                                                                                      \
        return std::make_unique<STATE_TYPE>(state_stack, context, user_ptr);                          \
    }

StateFactory::StateFactory(StateStack& state_stack, GameContext& context)
{
    m_factory[StateID::MAIN_MENU] = FACTORY_FUNCTION(MainMenuState);
    m_factory[StateID::GAME] = FACTORY_FUNCTION(GameState);
    m_factory[StateID::SETTINGS] = FACTORY_FUNCTION(SettingsState);
    m_factory[StateID::PAUSE] = FACTORY_FUNCTION(PauseState);
    m_factory[StateID::GAME_OVER] = FACTORY_FUNCTION(GameOverState);
    m_factory[StateID::KEY_BINDING] = FACTORY_FUNCTION(KeyBindingState);
    m_factory[StateID::PRE_GAME_LOADING_STATE] = FACTORY_FUNCTION(PreGameLoadingState);
}

std::unique_ptr<State> StateFactory::create_state(StateID id, void* user_ptr)
{
    if (auto result = m_factory.find(id);
        result != m_factory.end())
    {
        return result->second(user_ptr);
    }

    throw std::runtime_error("StateFactory::create_state - State not registered\n");
}
