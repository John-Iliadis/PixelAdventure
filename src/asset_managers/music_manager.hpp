//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_MUSIC_MANAGER_HPP
#define PLATFORMER_MUSIC_MANAGER_HPP

#include <SFML/Audio/Music.hpp>
#include "asset_manager.hpp"


class MusicManager : public AssetManager<MusicManager, sf::Music>
{
    friend AssetManager;
private:
    static std::unique_ptr<sf::Music> load(const std::string& file_name)
    {
        auto music = std::make_unique<sf::Music>();

        if (!music->openFromFile(file_name))
            throw std::runtime_error("MusicManager::load: Failed to load " + file_name);

        return music;
    }
};

#endif //PLATFORMER_MUSIC_MANAGER_HPP
