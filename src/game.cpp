//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


#define INITIAL_WINDOW_WIDTH 1280
#define INITIAL_WINDOW_HEIGHT 720

Game::Game()
{
    sf::VideoMode window_size {INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT};
    m_window.create(window_size, "Platformer");
    m_window.setFramerateLimit(get_max_refresh_rate());

    m_view = sf::View({0, 0, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT});

    m_texture_manager.load_directory("../assets/textures");
    m_font_manager.load_directory("../assets/fonts");
    m_sound_buffer_manager.load_directory("../assets/sounds");
    m_music_manager.load_directory("../assets/music");

    std::ifstream file("../data/tmx/test_map.tmj");

    if (!file.is_open())
    {
        throw std::runtime_error("Game::Game() - Failed to load map data\n");
    }

    m_map_data = nlohmann::json::parse(file);

    m_context.window = &m_window;
    m_context.view = &m_view;
    m_context.texture_manager = &m_texture_manager;
    m_context.font_manager = &m_font_manager;
    m_context.sound_buffer_manager = &m_sound_buffer_manager;
    m_context.music_manager = &m_music_manager;
    m_context.map_data = &m_map_data;

    m_state_stack = StateStack(m_context);
    m_state_stack.push(StateID::GAME);
    m_state_stack.apply_pending_changes();

    file.close();
}

void Game::run()
{
    const double time_per_frame = 1.0 / get_max_refresh_rate();
    double lag = 0;
    sf::Clock clock;

    while (m_window.isOpen())
    {
        lag += clock.restart().asSeconds();

        handle_events();

        while (lag >= time_per_frame)
        {
            update(time_per_frame);
            lag -= time_per_frame;
        }

        draw();
    }
}

void Game::handle_events()
{
    static sf::Event event{};

    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }

            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                    m_window.close();
                break;
            }

            case sf::Event::Resized:
            {
                m_view.setSize(event.size.width, event.size.height);
                break;
            }
        }

        m_state_stack.handle_events(event);
    }
}

void Game::update(double dt)
{
    m_state_stack.update(dt);
    m_window.setView(m_view);

    if (m_state_stack.empty())
        m_window.close();
}

void Game::draw()
{
    m_window.clear({33, 31, 48, 255});
    m_state_stack.draw();
    m_window.display();
}
