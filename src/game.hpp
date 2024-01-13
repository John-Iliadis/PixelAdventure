//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_GAME_HPP
#define PLATFORMER_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "utils.hpp"
#include "states/state_stack.hpp"
#include "asset_managers/texture_manager.hpp"
#include "asset_managers/font_manager.hpp"
#include "asset_managers/sound_buffer_manager.hpp"
#include "asset_managers/music_manager.hpp"


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
    sf::RenderWindow m_window;
    StateStack state_stack;
    GameContext context;
    TextureManager texture_manager;
    FontManager font_manager;
    SoundBufferManager sound_buffer_manager;
    MusicManager music_manager;
};


#endif //PLATFORMER_GAME_HPP
