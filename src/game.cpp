//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


static constexpr uint32_t window_width = 1920;
static constexpr uint32_t window_height = 1080;
static constexpr uint32_t world_view_width = window_width / 2;
static constexpr uint32_t world_view_height = window_height / 2;

Game::Game()
{
    sf::VideoMode window_size {window_width, window_height};
    m_window.create(window_size, "Platformer", sf::Style::Titlebar | sf::Style::Close);
    m_window.setKeyRepeatEnabled(false);

    m_world_camera = Camera(world_view_width, world_view_height);
    m_gui_view = sf::View({0, 0}, {window_width, window_height});

    m_texture_manager.load_directory("../assets/textures");
    m_font_manager.load_directory("../assets/fonts");
    m_sound_buffer_manager.load_directory("../assets/sounds");
    m_music_manager.load_directory("../assets/music");

    m_context.window = &m_window;
    m_context.world_camera = &m_world_camera;
    m_context.gui_view = &m_gui_view;
    m_context.texture_manager = &m_texture_manager;
    m_context.font_manager = &m_font_manager;
    m_context.sound_buffer_manager = &m_sound_buffer_manager;
    m_context.music_manager = &m_music_manager;

    LevelDetails level_details {
        "../data/tmx/test_map3.tmj",
        "test_map3",
        "yellow"
    };

    auto level_details_ptr = reinterpret_cast<UINT_PTR>(&level_details);
    
    m_state_stack = StateStack(m_context);
    m_state_stack.push(StateID::MAIN_MENU, level_details_ptr);
    m_state_stack.apply_pending_changes();
}

void Game::run()
{
    const double time_per_frame = 1.0 / 240;
    double ellapsed = 0;
    sf::Clock clock;

    while (m_window.isOpen())
    {
        sf::Time elapsed_time = clock.restart();
        ellapsed += elapsed_time.asSeconds();

        handle_events();

        while (ellapsed >= time_per_frame)
        {
            update(time_per_frame);
            ellapsed -= time_per_frame;
        }

        update_fps_stats(elapsed_time);
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
        }

        m_state_stack.handle_events(event);
    }
}

void Game::update(double dt)
{
    m_state_stack.update(dt);

    if (m_state_stack.empty())
        m_window.close();
}

void Game::draw()
{
    m_window.clear(sf::Color(33, 31, 48, 255));
    m_state_stack.draw();
    m_window.display();
}

void Game::update_fps_stats(sf::Time elapsed)
{
    fps_update_time += elapsed;
    fps_num_frames += 1;

    if (fps_update_time >= sf::seconds(1.f))
    {
        std::cout << fps_num_frames << '\n';

        fps_update_time -= sf::seconds(1);
        fps_num_frames = 0;
    }
}
