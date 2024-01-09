//
// Created by Gianni on 9/01/2024.
//

#include "game.hpp"


Game::Game()
{
    sf::VideoMode window_size {1920, 1080};
    window.create(window_size, "Platformer");
    window.setFramerateLimit(get_max_refresh_rate());
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
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

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
    }
}

void Game::update(double dt)
{

}

void Game::draw()
{
    window.clear();
    window.display();
}
