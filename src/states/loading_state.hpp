//
// Created by Gianni on 13/02/2024.
//

#ifndef PLATFORMER_PRE_GAME_LOADING_STATE_HPP
#define PLATFORMER_PRE_GAME_LOADING_STATE_HPP

#include <memory>
#include <thread>
#include <atomic>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../asset_managers/font_manager.hpp"
#include "../utilities/utils.hpp"
#include "../world/world.hpp"
#include "../world/parallel_task.hpp"
#include "state.hpp"


class LoadingState : public State
{
public:
    LoadingState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);
    ~LoadingState();

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    std::thread m_loading_thread;
    std::unique_ptr<ParallelTask> m_task;
    sf::Text m_loading_text;
    std::string m_loading_string;
    float m_ellapsed;
    float m_string_timer;
    float m_min_active_duration;
    std::atomic<bool> m_load_complete;
};


#endif //PLATFORMER_PRE_GAME_LOADING_STATE_HPP
