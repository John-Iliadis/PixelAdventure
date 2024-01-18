//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_TILE_MAP_HPP
#define PLATFORMER_TILE_MAP_HPP

#include <vector>
#include <cstdint>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../vendor/json.hpp"
#include "../states/game_context.hpp"
#include "../asset_managers/texture_manager.hpp"


class TileMap : public sf::Drawable
{
public:
    TileMap(GameContext& context, const std::string& file_name);

    const std::vector<sf::FloatRect>& get_colliders() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<sf::FloatRect> m_colliders;
    sf::Sprite m_map_sprite;
    sf::Vector2u window_size;
};


#endif //PLATFORMER_TILE_MAP_HPP
