//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_GAME_CONTEXT_HPP
#define PLATFORMER_GAME_CONTEXT_HPP

namespace sf
{
    class RenderWindow;
}

class Settings;

struct GameContext
{
    sf::RenderWindow* window = nullptr;
    Settings* settings = nullptr;
};

#endif //PLATFORMER_GAME_CONTEXT_HPP
