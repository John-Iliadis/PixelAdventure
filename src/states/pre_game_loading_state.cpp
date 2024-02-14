//
// Created by Gianni on 13/02/2024.
//

#include "pre_game_loading_state.hpp"


PreGameLoadingState::PreGameLoadingState(StateStack &state_stack, GameContext &context, void *user_ptr)
    : State(state_stack, context)
    , m_level_details(reinterpret_cast<LevelDetails*>(user_ptr))
    , m_loading_string("Loading")
    , m_ellapsed()
    , m_string_timer()
    , m_min_active_duration(utils::random(2, 5))
    , m_load_complete(false)
{
    m_loading_text.setFont(m_context.font_manager->get("bulky_pixel"));
    m_loading_text.setString(m_loading_string);
    m_loading_text.setCharacterSize(30);
    m_loading_text.setPosition(1500, 900);

    m_loading_thread = std::thread {
            [this] () {
                m_world = new World(m_context, *m_level_details);
                m_load_complete = true;
            }
    };
}

bool PreGameLoadingState::handle_events(const sf::Event &event)
{
    return false;
}

bool PreGameLoadingState::update(double dt)
{
    m_ellapsed += dt;
    m_string_timer += dt;

    if (m_ellapsed > m_min_active_duration && m_load_complete)
    {
        void* user_ptr = reinterpret_cast<void*>(m_world);

        request_stack_clear();
        request_stack_push(StateID::GAME, user_ptr);
    }

    if (m_string_timer > 0.3)
    {
        if (m_loading_string.length() % std::string("Loading...").length() == 0)
            m_loading_string = "Loading";
        else
            m_loading_string.push_back('.');

        m_loading_text.setString(m_loading_string);
        m_string_timer = 0;
    }

    return false;
}

void PreGameLoadingState::on_world_draw()
{
}

void PreGameLoadingState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_loading_text);
}

PreGameLoadingState::~PreGameLoadingState()
{
    if (m_loading_thread.joinable())
    {
        m_loading_thread.join();
    }
}
