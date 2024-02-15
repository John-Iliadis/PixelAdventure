//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_GAME_HPP
#define PLATFORMER_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include <iostream>
#include "utilities/utils.hpp"
#include "vendor/json.hpp"
#include "states/state_stack.hpp"
#include "asset_managers/texture_manager.hpp"
#include "asset_managers/font_manager.hpp"
#include "asset_managers/sound_buffer_manager.hpp"
#include "asset_managers/music_manager.hpp"
#include "camera/camera.hpp"
#include "structs/level_details.hpp"
#include "structs/settings.hpp"
#include "audio/sound_player.hpp"
#include "audio/music_player.hpp"
#include "world/cursor.hpp"


class Game
{
public:
    Game();
    void run();

private:
    void handle_events();
    void update(double dt);
    void draw();

    void update_fps_stats(sf::Time elapsed);

private:
    sf::RenderWindow m_window;
    Camera m_world_camera;
    Camera m_gui_camera;
    StateStack m_state_stack;
    GameContext m_context;
    TextureManager m_texture_manager;
    FontManager m_font_manager;
    SoundBufferManager m_sound_buffer_manager;
    MusicManager m_music_manager;
    Settings m_settings;

    sf::Time fps_update_time{};
    uint32_t fps_num_frames{};
};


#endif //PLATFORMER_GAME_HPP
