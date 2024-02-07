//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_GAME_CONTEXT_HPP
#define PLATFORMER_GAME_CONTEXT_HPP


namespace sf
{
    class RenderWindow;
}

class Camera;
class Settings;
class TextureManager;
class FontManager;
class SoundBufferManager;
class MusicManager;

struct GameContext
{
    sf::RenderWindow* window;
    Camera* world_camera;
    Camera* gui_camera;
    TextureManager* texture_manager;
    FontManager* font_manager;
    SoundBufferManager* sound_buffer_manager;
    MusicManager* music_manager;
    Settings* settings;
};

#endif //PLATFORMER_GAME_CONTEXT_HPP
