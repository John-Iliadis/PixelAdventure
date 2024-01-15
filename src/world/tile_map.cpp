//
// Created by Gianni on 13/01/2024.
//

#include "tile_map.hpp"


constexpr int tile_scale = 2; // todo: put in json file

TileMap::TileMap(GameContext& context, const std::string &file_name)
{
    auto& map_data = *context.map_data;

    window_size = context.window->getSize();

    m_map_sprite.setTexture(context.texture_manager->get("test_map"));
    m_map_sprite.setScale(tile_scale, tile_scale);

    const uint32_t tile_width = map_data["tilewidth"].get<uint32_t>();
    const uint32_t tile_height = map_data["tileheight"].get<uint32_t>();

    const uint32_t total_tiles_x = map_data["width"].get<uint32_t>();
    const uint32_t total_tiles_y = map_data["height"].get<uint32_t>();

    std::vector<int> tile_codes = map_data["layers"][0]["data"].get<std::vector<int>>();

    for (int i = 0; i < total_tiles_y; ++i)
    {
        for (int j = 0; j < total_tiles_x; ++j)
        {
            if (tile_codes.at(i * total_tiles_x + j) != 0)
            {
                sf::FloatRect collider_rect {
                        static_cast<float>(j * tile_width * tile_scale),
                        static_cast<float>(i * tile_height * tile_scale),
                        static_cast<float>(tile_width * tile_scale),
                        static_cast<float>(tile_height * tile_scale)
                };

                m_colliders.push_back(std::move(collider_rect));
            }
        }
    }
}

const std::vector<sf::FloatRect>& TileMap::get_colliders() const
{
    return m_colliders;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_map_sprite);
}
