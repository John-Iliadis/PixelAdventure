//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_SOUND_BUFFER_MANAGER_HPP
#define PLATFORMER_SOUND_BUFFER_MANAGER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include "asset_manager.hpp"


class SoundBufferManager : public AssetManager<SoundBufferManager, sf::SoundBuffer>
{
    friend AssetManager;
private:
    static std::unique_ptr<sf::SoundBuffer> load(const std::string& file_name)
    {
        auto sound_buffer = std::make_unique<sf::SoundBuffer>();

        if (!sound_buffer->loadFromFile(file_name))
            throw std::runtime_error("SoundBufferManager::load: Failed to load " + file_name);

        return sound_buffer;
    }
};

#endif //PLATFORMER_SOUND_BUFFER_MANAGER_HPP
