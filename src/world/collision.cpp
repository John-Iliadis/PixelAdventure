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
        {
            *t_intersection_near = l_t_intersection_near;
        }

        if (contact_point)
        {
            *contact_point = ray_origin + l_t_intersection_near * ray_dir;
        }

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

    bool dynamic_rect_vs_rect(const sf::FloatRect& movable, const sf::Vector2f& velocity, const sf::FloatRect& target,
                              sf::Vector2f* contact_point, sf::Vector2f* contact_normal,
                              float* t)
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

        if (ray_vs_rect(ray_origin, velocity, expanded_rect, contact_point, contact_normal, t))
            return (*t >= 0.f && *t < 1.f);

        return false;
    }
};
