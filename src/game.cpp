//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


Game::Game()
{
    sf::VideoMode window_size {1920, 1080};
    m_window.create(window_size, "Platformer");
    m_window.setFramerateLimit(get_max_refresh_rate());

    auto context = std::make_shared<GameContext>();
    context->window = &m_window;

    state_stack = StateStack(context);
    state_stack.push(StateID::MAIN_MENU);
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
