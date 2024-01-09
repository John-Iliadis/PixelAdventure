//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_RESOURSE_MANAGER_HPP
#define PLATFORMER_RESOURSE_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <stdexcept>


template <typename Derived, typename asset_type>
class ResourceManager
{
public:
    ResourceManager() = default;
    virtual ~ResourceManager() = default;

    asset_type& get(const std::string& key);
    //const asset_type& get(const std::string& key) const;

    void load(const std::string& key, const std::string& file_name);
    void load_directory(const std::string& dir);
    void remove(const std::string& key);

private:
    std::unordered_map<std::string, std::unique_ptr<asset_type>> map;
};


#include "resource_manager.inl"

//#include <SFML/Audio/SoundBuffer.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/Font.hpp>
//
//typedef ResourceManager<sf::Texture> Textures;
//typedef ResourceManager<sf::Font> Fonts;
//typedef ResourceManager<sf::SoundBuffer> SoundBuffers;

#endif //PLATFORMER_RESOURSE_MANAGER_HPP
