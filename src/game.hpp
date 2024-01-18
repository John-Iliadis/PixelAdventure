//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_GAME_HPP
#define PLATFORMER_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include "utilities/utils.hpp"
#include "vendor/json.hpp"
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
    sf::View m_view;
    StateStack m_state_stack;
    GameContext m_context;
    TextureManager m_texture_manager;
    FontManager m_font_manager;
    SoundBufferManager m_sound_buffer_manager;
    MusicManager m_music_manager;
    nlohmann::json m_map_data;
};


#endif //PLATFORMER_GAME_HPP
