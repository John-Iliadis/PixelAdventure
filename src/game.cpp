//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


Game::Game()
{
    sf::VideoMode window_size {1280, 720};
    m_window.create(window_size, "Platformer");
    m_window.setFramerateLimit(get_max_refresh_rate());

    texture_manager.load_directory("../assets/textures");
    font_manager.load_directory("../assets/fonts");
    sound_buffer_manager.load_directory("../assets/sounds");
    music_manager.load_directory("../assets/music");

    context.window = &m_window;
    context.texture_manager = &texture_manager;
    context.font_manager = &font_manager;
    context.sound_buffer_manager = &sound_buffer_manager;
    context.music_manager = &music_manager;

    state_stack = StateStack(context);
    state_stack.push(StateID::GAME);
    state_stack.apply_pending_changes();
}

void Game::run()
{
    sf::Clock clock;

    while (m_window.isOpen())
    {
        double dt = clock.restart().asSeconds();
        handle_events();
        update(dt);
        draw();
    }
}

void Game::handle_events()
{
    static sf::Event event{};

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
                m_window.close();

        if (state_stack.empty())
            m_window.close();

        state_stack.handle_events(event);
    }
}

void Game::update(double dt)
{
    state_stack.update(dt);
}

void Game::draw()
{
    m_window.clear();
    state_stack.draw();
    m_window.display();
}
