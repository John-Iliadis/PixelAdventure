//
// Created by Gianni on 13/02/2024.
//

#include "loading_state.hpp"


LoadingState::LoadingState(StateStack &state_stack, GameContext &context, void *user_ptr)
    : State(state_stack, context)
    , m_task(reinterpret_cast<ParallelTask*>(user_ptr))
    , m_loading_string("Loading")
    , m_ellapsed()
    , m_string_timer()
    , m_min_active_duration(static_cast<float>(utils::random(2, 5)))
    , m_load_complete(false)
{
    m_loading_text.setFont(m_context.font_manager->get("bulky_pixel"));
    m_loading_text.setString(m_loading_string);
    m_loading_text.setCharacterSize(30);
    m_loading_text.setPosition(1500, 900);

    m_loading_thread = std::thread {
        [this] () {
            m_task->execute();
            m_load_complete = true;
        }
    };
}

bool LoadingState::handle_events(const sf::Event &event)
{
    return false;
}

bool LoadingState::update(double dt)
{
    m_ellapsed += static_cast<float>(dt);
    m_string_timer += static_cast<float>(dt);

    if (m_ellapsed > m_min_active_duration && m_load_complete)
    {
        void* user_ptr = nullptr;

        if (m_task->has_output())
        {
            user_ptr = m_task->get_output();
            assert(user_ptr);
        }

        request_stack_clear();
        request_stack_push(m_task->m_next_state, user_ptr);
    }

    if (m_string_timer > 0.3)
    {
        if (m_loading_string.length() % std::string("Loading...").length() == 0)
        {
            m_loading_string = "Loading";
        }
        else
        {
            m_loading_string.push_back('.');
        }

        m_loading_text.setString(m_loading_string);
        m_string_timer = 0;
    }

    return false;
}

void LoadingState::on_world_draw()
{
}

void LoadingState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_loading_text);
}

LoadingState::~LoadingState()
{
    if (m_loading_thread.joinable())
    {
        m_loading_thread.join();
    }
}
