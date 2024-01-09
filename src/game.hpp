//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_GAME_HPP
#define PLATFORMER_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "utils.hpp"


class Game
{
public:
    Game();
    void run();

private:
    void handle_events();
    void update(double dt);
    void draw();

private:
    sf::RenderWindow window;
};


#endif //PLATFORMER_GAME_HPP
