//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


//static constexpr uint32_t window_width = 1920;
//static constexpr uint32_t window_height = 1080;
//static constexpr uint32_t world_view_width = window_width / 2;
//static constexpr uint32_t world_view_height = window_height / 2;

Game::Game()
{
    sf::VideoMode window_size;

    sf::Vector2u desktop_mode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

    uint32_t window_style;

    if (desktop_mode.x <= 1920 || desktop_mode.y <= 1080)
    {
        window_size = {desktop_mode.x, desktop_mode.y};
        window_style = sf::Style::Fullscreen;
    }
    else
    {
        window_size = {1920, 1080};
        window_style = sf::Style::Titlebar | sf::Style::Close;
    }

    m_window.create(window_size, "Pixel Adventure", window_style);
    m_window.setKeyRepeatEnabled(false);

    Cursor::init();
    Cursor::select_window(&m_window);

    m_world_camera = Camera(window_size.width / 2, window_size.height / 2);

    m_gui_camera = Camera(window_size.width, window_size.height);
    m_gui_camera.set_center(m_window.getDefaultView().getCenter());

    m_font_manager.load_directory("../assets/fonts");

    m_context.window = &m_window;
    m_context.world_camera = &m_world_camera;
    m_context.gui_camera = &m_gui_camera;
    m_context.texture_manager = &m_texture_manager;
    m_context.font_manager = &m_font_manager;
    m_context.sound_buffer_manager = &m_sound_buffer_manager;
    m_context.music_manager = &m_music_manager;
    m_context.settings = &m_settings;

    m_state_stack = StateStack(m_context);
    m_state_stack.push(StateID::LOADING_STATE, new LoadAssets(m_context, StateID::MAIN_MENU));
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

        while (ellapsed >= time_per_frame)
        {
            ellapsed -= time_per_frame;
            handle_events();
            update(time_per_frame);
        }

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
    Cursor::set_item_selected(false);
    m_state_stack.update(dt);

    m_state_stack.empty()? m_window.close() : void();
    m_gui_camera.update(dt);

    SoundPlayer::update(m_sound_buffer_manager, m_settings.sound_volume);
    MusicPlayer::update(m_music_manager, m_settings.music_volume);
}

void Game::draw()
{
    static const sf::Color clear_color(33, 31, 48, 255);

    Cursor::set_cursor();
    m_window.clear(clear_color);
    m_state_stack.draw();
    m_window.display();
}
