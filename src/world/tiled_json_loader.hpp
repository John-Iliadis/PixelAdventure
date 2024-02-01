//
// Created by Gianni on 29/01/2024.
//

#ifndef PLATFORMER_TILED_JSON_LOADER_HPP
#define PLATFORMER_TILED_JSON_LOADER_HPP

#include <vector>
#include <algorithm>
#include <cassert>
#include <SFML/Graphics/Rect.hpp>
#include "../vendor/json.hpp"
#include "../structs/map_data.hpp"


namespace TiledJsonLoader
{
    // gets tile width, height and tile count
    MapData get_map_data(const nlohmann::json& json_data);

    // returns a tiled layer json object
    nlohmann::json get_layer(const nlohmann::json& json_data, const std::string& layer_name);

    // returns tile rectangles in world coordinates
    std::vector<sf::Rect<float>> get_tiles(const nlohmann::json& json_data, const std::string& layer_name);

    // returns the first position that matches pos_name
    sf::Vector2f get_position(const nlohmann::json& json_data, const std::string& layer_name, const std::string& pos_name);

    // returns all positions that match pos_name. All positions start at top left
    std::vector<sf::Vector2f> get_positions(const nlohmann::json& json_data, const std::string& layer_name, const std::string& pos_name);

    // returns a property from a property array
    template <typename T>
    T get_property(const nlohmann::json& property_array, const std::string& property_name);
}

#include "tiled_json_loader.inl"


#endif //PLATFORMER_TILED_JSON_LOADER_HPP
