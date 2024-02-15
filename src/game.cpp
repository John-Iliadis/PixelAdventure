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

    Cursor::init();
    Cursor::select_window(&m_window);

    m_world_camera = Camera(world_view_width, world_view_height);

    m_gui_camera = Camera(window_width, window_height);
    m_gui_camera.set_center(m_window.getDefaultView().getCenter());

    m_texture_manager.load_directory("../assets/textures");
    m_font_manager.load_directory("../assets/fonts");
    m_sound_buffer_manager.load_directory("../assets/sounds");
    m_music_manager.load_directory("../assets/music");
    m_settings.load_from_file("../data/settings/settings.json");

    m_context.window = &m_window;
    m_context.world_camera = &m_world_camera;
    m_context.gui_camera = &m_gui_camera;
    m_context.texture_manager = &m_texture_manager;
    m_context.font_manager = &m_font_manager;
    m_context.sound_buffer_manager = &m_sound_buffer_manager;
    m_context.music_manager = &m_music_manager;
    m_context.settings = &m_settings;

    m_state_stack = StateStack(m_context);
    m_state_stack.push(StateID::MAIN_MENU);
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

    m_settings.save_to_file("../data/settings/settings.json");
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
        }

        m_state_stack.handle_events(event);
    }
}

void Game::update(double dt)
{
    m_state_stack.update(dt);
    m_state_stack.empty()? m_window.close() : void();
    m_gui_camera.update(dt);

    SoundPlayer::update(m_sound_buffer_manager, m_settings.sound_volume);
    MusicPlayer::update(m_music_manager, m_settings.music_volume);
}

void Game::draw()
{
    static const sf::Color clear_color(33, 31, 48, 255);

    m_window.clear(clear_color);
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
