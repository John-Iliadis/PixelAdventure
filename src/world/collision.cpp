//
// Created by Gianni on 14/01/2024.
//

#include "collision.hpp"


namespace Collision
{
    bool point_vs_rect(const sf::Vector2f& point, const sf::FloatRect& rect)
    {
        return (point.x >= rect.left && point.x < (rect.left + rect.width) &&
                point.y >= rect.top && point.y < (rect.top + rect.height));
    }

    bool rect_vs_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
    {
        return (rect1.left < (rect2.left + rect2.width) && rect1.top < (rect2.top + rect2.height) &&
                (rect1.left + rect1.width) > rect2.left && (rect1.top + rect1.height) > rect2.top);
    }

    bool ray_vs_rect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir, const sf::FloatRect& rect,
                     sf::Vector2f* contact_point, sf::Vector2f* contact_normal,
                     float* t_intersection_near)
    {
        sf::Vector2f t_near = (rect.getPosition() - ray_origin);
        t_near.x /= ray_dir.x;
        t_near.y /= ray_dir.y;

        sf::Vector2f t_far = (rect.getPosition() + rect.getSize() - ray_origin);
        t_far.x /= ray_dir.x;
        t_far.y /= ray_dir.y;

        if (std::isnan(t_far.y) || std::isnan(t_far.x) || std::isnan(t_near.y) || std::isnan(t_near.x))
            return false;

        if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

        if (t_near.x > t_far.y || t_near.y > t_far.x)
            return false;

        float l_t_intersection_near = std::max(t_near.x, t_near.y);
        float t_intersection_far = std::min(t_far.x, t_far.y);

        if (t_intersection_far < 0)
            return false;

        if (t_intersection_near)
            *t_intersection_near = l_t_intersection_near;

        if (contact_point)
            *contact_point = ray_origin + l_t_intersection_near * ray_dir;

        if (contact_normal)
        {
            if (t_near.x > t_near.y)
            {
                if (ray_dir.x < 0)
                    *contact_normal = {1, 0};
                else
                    *contact_normal = {-1, 0};
            }
            else if (t_near.x < t_near.y)
            {
                if (ray_dir.y < 0)
                    *contact_normal = {0, 1};
                else
                    *contact_normal = {0, -1};
            }
        }

        return true;
    }

    bool ray_cast(const sf::FloatRect& movable, const sf::Vector2f& velocity, const sf::FloatRect& target)
    {
        if (!velocity.x && !velocity.y)
            return false;

        sf::Vector2f target_pos = target.getPosition();
        sf::Vector2f target_size = target.getSize();
        sf::Vector2f movable_size = movable.getSize();

        sf::FloatRect expanded_rect {
                target_pos.x - movable_size.x / 2.f,
                target_pos.y - movable_size.y / 2.f,
                target_size.x + movable_size.x,
                target_size.y + movable_size.y
        };

        sf::Vector2f ray_origin {movable.left + movable.width / 2.f, movable.top + movable.height / 2.f};

        float t{};

        if (ray_vs_rect(ray_origin, velocity, expanded_rect, nullptr, nullptr, &t))
            return (t >= 0.f && t < 1.f);

        return false;
    }

    static std::vector<std::pair<uint32_t, sf::FloatRect>> get_colliding_rectangle_indexes(Player& player, const std::vector<sf::FloatRect>& map_tiles)
    {
        std::vector<std::pair<uint32_t, sf::FloatRect>> rects;

        for (int i = 0; i < map_tiles.size(); ++i)
        {
            sf::FloatRect l_rect;

            if (player.get_hitbox().intersects(map_tiles.at(i), l_rect))
                rects.emplace_back(i, std::move(l_rect));
        }

        return rects;
    }

    void handle_x_axis_collisions(Player& player, TileMap& tile_map, double dt)
    {
        std::vector<std::pair<uint32_t, sf::FloatRect>> colliding_rectangles;
        const auto& map_tiles = tile_map.get_colliders();
        auto velocity = player.get_velocity();
        player.set_touching_wall(false);

        for (const auto& tile : map_tiles)
        {
            sf::Vector2f l_velocity = player.get_orientation() == SpriteOrientation::FACES_RIGHT? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0);

            if (ray_cast(player.get_hitbox(), l_velocity, tile))
            {
                player.set_touching_wall(true);
                break;
            }
        }

        if (velocity.x == 0) return;

        player.move(velocity.x * dt, 0);

        colliding_rectangles = get_colliding_rectangle_indexes(player, map_tiles);

        if (colliding_rectangles.empty()) return;

        std::sort(colliding_rectangles.begin(), colliding_rectangles.end(),
                  [] (const std::pair<uint32_t, sf::FloatRect>& a, const std::pair<uint32_t, sf::FloatRect>& b) {
                      return a.second.width > b.second.width;
                  });

        uint32_t highest_overlapping_rect_index = colliding_rectangles.front().first;

        if (velocity.x > 0)
        {
            float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().x -
                    player.get_hitbox().width / 2.f;
            player.set_position(new_pos, player.get_position().y);
        }
        else
        {
            float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().x
                    + map_tiles.at(highest_overlapping_rect_index).width + player.get_hitbox().width / 2.f;
            player.set_position(new_pos, player.get_position().y);
        }

        player.set_velocity(0, velocity.y);
    }

    void handle_y_axis_collisions(Player& player, TileMap& tile_map, double dt)
    {
        std::vector<std::pair<uint32_t, sf::FloatRect>> colliding_rectangles;
        const auto& map_tiles = tile_map.get_colliders();
        auto velocity = player.get_velocity();

        if (velocity.y == 0) return;

        player.move(0, velocity.y * dt);
        colliding_rectangles = get_colliding_rectangle_indexes(player, map_tiles);

        if (colliding_rectangles.empty()) return;

        std::sort(colliding_rectangles.begin(), colliding_rectangles.end(),
                  [] (const std::pair<uint32_t, sf::FloatRect>& a, const std::pair<uint32_t, sf::FloatRect>& b) {
                      return a.second.height > b.second.height;
                  });

        uint32_t highest_overlapping_rect_index = colliding_rectangles.front().first;

        if (velocity.y > 0)
        {
            float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().y;
            player.set_position(player.get_position().x, new_pos);
        }
        else
        {
            float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().y +
                    map_tiles.at(highest_overlapping_rect_index).height + player.get_hitbox().height;
            player.set_position(player.get_position().x, new_pos);
        }

        player.set_velocity(velocity.x, 0);
    }
};
