//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_GAME_CONTEXT_HPP
#define PLATFORMER_GAME_CONTEXT_HPP

#include "../json.hpp"


namespace sf
{
    class RenderWindow;
    class View;
}

class Settings;
class TextureManager;
class FontManager;
class SoundBufferManager;
class MusicManager;

struct GameContext
{
    sf::RenderWindow* window = nullptr;
    sf::View* view = nullptr;
    TextureManager* texture_manager = nullptr;
    FontManager* font_manager = nullptr;
    SoundBufferManager* sound_buffer_manager = nullptr;
    MusicManager* music_manager = nullptr;
    Settings* settings = nullptr;
    nlohmann::json* map_data = nullptr;
};

#endif //PLATFORMER_GAME_CONTEXT_HPP
