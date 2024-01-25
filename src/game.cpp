//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


#define INITIAL_WINDOW_WIDTH 1280
#define INITIAL_WINDOW_HEIGHT 720
#define INITIAL_VIEWPORT_WIDTH INITIAL_WINDOW_WIDTH / 2
#define INITIAL_VIEWPORT_HEIGHT INITIAL_WINDOW_HEIGHT / 2

Game::Game()
{
    sf::VideoMode window_size {INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT};
    m_window.create(window_size, "Platformer");
    m_window.setKeyRepeatEnabled(false);
    m_window.setFramerateLimit(240); // todo: implement in game loop

    m_view = sf::View({0, 0, INITIAL_VIEWPORT_WIDTH, INITIAL_VIEWPORT_HEIGHT});

    m_texture_manager.load_directory("../assets/textures");
    m_font_manager.load_directory("../assets/fonts");
    m_sound_buffer_manager.load_directory("../assets/sounds");
    m_music_manager.load_directory("../assets/music");

    m_context.window = &m_window;
    m_context.view = &m_view;
    m_context.texture_manager = &m_texture_manager;
    m_context.font_manager = &m_font_manager;
    m_context.sound_buffer_manager = &m_sound_buffer_manager;
    m_context.music_manager = &m_music_manager;

    m_state_stack = StateStack(m_context);
    m_state_stack.push(StateID::GAME);
    m_state_stack.apply_pending_changes();
}

void Game::run()
{
    const double time_per_frame = 1.0 / utils::get_max_refresh_rate();
    double ellapsed = 0;
    sf::Clock clock;

    while (m_window.isOpen())
    {
        sf::Time elapsed_time = clock.restart();
        ellapsed += elapsed_time.asSeconds();

        while (ellapsed >= time_per_frame)
        {
            handle_events();
            update(time_per_frame);
            ellapsed -= time_per_frame;
        }

        update_fps_stats(elapsed_time);
        draw(); // todo: limit frame rate
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
                float aspect_ratio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
                m_view.setSize(int(INITIAL_VIEWPORT_HEIGHT * aspect_ratio), int(INITIAL_VIEWPORT_HEIGHT));
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
