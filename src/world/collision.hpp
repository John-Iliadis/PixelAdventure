//
// Created by Gianni on 14/01/2024.
//

#ifndef PLATFORMER_COLLISION_HPP
#define PLATFORMER_COLLISION_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include "tile_map.hpp"
#include "player/player.hpp"


namespace Collision
{
    bool point_vs_rect(const sf::Vector2f& point, const sf::FloatRect& rect);
    bool rect_vs_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

    bool ray_vs_rect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir, const sf::FloatRect& rect,
                     sf::Vector2f* contact_point = nullptr, sf::Vector2f* contact_normal = nullptr,
                     float* t_intersection_near = nullptr);

    bool ray_cast(const sf::FloatRect& movable, const sf::Vector2f& velocity, const sf::FloatRect& target);

    void handle_x_axis_collisions(Player& player, TileMap& tile_map, double dt);
    void handle_y_axis_collisions(Player& player, TileMap& tile_map, double dt);
};


#endif //PLATFORMER_COLLISION_HPP
