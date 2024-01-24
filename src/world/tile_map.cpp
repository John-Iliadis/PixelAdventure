//
// Created by Gianni on 13/01/2024.
//

#include "tile_map.hpp"


TileMap::TileMap(const std::string &file_name)
{
    if (!map_texture.loadFromFile("../assets/textures/test_map2.png"))
        throw std::runtime_error("TileMap::TileMap - Failed to load texture\n");

    m_map_sprite.setTexture(map_texture);

    std::ifstream file(file_name);

    if (!file.is_open())
        throw std::runtime_error("TileMap::TileMap - Failed to open file" + file_name + '\n');

    nlohmann::json map_data = nlohmann::json::parse(file);

    file.close();

    tile_width = map_data["tilewidth"].get<uint32_t>();
    tile_height = map_data["tileheight"].get<uint32_t>();

    total_tiles_x = map_data["width"].get<uint32_t>();
    total_tiles_y = map_data["height"].get<uint32_t>();

    auto get_data = [&map_data] (const std::string& layer_name) {

        auto itr = std::find_if(map_data["layers"].begin(), map_data["layers"].end(),
        [&layer_name] (const nlohmann::json& layer) {
                return (layer["name"].get<std::string>() == layer_name);
        });

        assert(itr != map_data["layers"].end());

        return (*itr)["data"].get<std::vector<int>>();
    };

    std::vector<int> solid_tiles = get_data("solid_tiles");
    std::vector<int> enemy_colliders = get_data("enemy_colliders");
    std::vector<int> enemy_spawn_positions = get_data("enemy_layer");

    setup_tiles(solid_tiles, m_solid_tiles);
    setup_tiles(enemy_colliders, m_enemy_colliders);
    setup_positions(enemy_spawn_positions, m_enemy_spawn_positions);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_map_sprite);
}

const std::vector<sf::FloatRect> &TileMap::get_solid_tiles() const
{
    return m_solid_tiles;
}

const std::vector<sf::FloatRect> &TileMap::get_enemy_colliders() const
{
    return m_enemy_colliders;
}

const std::vector<std::pair<uint32_t, sf::Vector2f>>& TileMap::get_enemy_spawn_positions() const
{
    return m_enemy_spawn_positions;
}

void TileMap::setup_tiles(const std::vector<int> &data, std::vector<sf::FloatRect> &tiles)
{
    for (int i = 0; i < total_tiles_y; ++i)
    {
        for (int j = 0; j < total_tiles_x; ++j)
        {
            if (data.at(i * total_tiles_x + j) != 0)
            {
                sf::FloatRect collider_rect {
                        static_cast<float>(j * tile_width),
                        static_cast<float>(i * tile_height),
                        static_cast<float>(tile_width),
                        static_cast<float>(tile_height)
                };

                tiles.push_back(std::move(collider_rect));
            }
        }
    }
}

void TileMap::setup_positions(const std::vector<int> &data, std::vector<std::pair<uint32_t, sf::Vector2f>>& positions)
{
    for (int i = 0; i < total_tiles_y; ++i)
    {
        for (int j = 0; j < total_tiles_x; ++j)
        {
            uint32_t entity_id = data.at(i * total_tiles_x + j);

            if (entity_id != 0)
            {
                float x_pos = j * tile_width + tile_width / 2.f;
                float y_pos = (i + 1) * tile_height;

                positions.emplace_back(std::make_pair(entity_id, sf::Vector2f(x_pos, y_pos)));
            }
        }
    }
}
