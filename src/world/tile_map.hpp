//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_TILE_MAP_HPP
#define PLATFORMER_TILE_MAP_HPP

#include <vector>
#include <cstdint>
#include <fstream>
#include <algorithm>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../vendor/json.hpp"
#include "../states/game_context.hpp"
#include "../asset_managers/texture_manager.hpp"


class TileMap : public sf::Drawable
{
public:
    TileMap(const std::string& file_name);

    const std::vector<sf::FloatRect>& get_solid_tiles() const;
    const std::vector<sf::FloatRect>& get_enemy_colliders() const; // todo: change name
    const std::vector<std::pair<uint32_t, sf::Vector2f>>& get_enemy_spawn_positions() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setup_tiles(const std::vector<int>& data, std::vector<sf::FloatRect>& tiles);
    void setup_positions(const std::vector<int>& data, std::vector<std::pair<uint32_t, sf::Vector2f>>& positions);

private:
    std::vector<sf::FloatRect> m_solid_tiles;
    std::vector<sf::FloatRect> m_enemy_colliders;
    std::vector<std::pair<uint32_t, sf::Vector2f>> m_enemy_spawn_positions;

    uint32_t tile_width;
    uint32_t tile_height;
    uint32_t total_tiles_x;
    uint32_t total_tiles_y;

    sf::Sprite m_map_sprite;
    sf::Texture map_texture;
};


#endif //PLATFORMER_TILE_MAP_HPP
