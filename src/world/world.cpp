//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"


World::World(GameContext& context)
    : m_context(context)
    , m_tile_map(m_context, "../data/tmx/test_map.tmj")
    , m_background(*m_context.texture_manager, m_context.window->getSize())
    , m_player(*context.texture_manager)
{
}

void World::handle_events(const sf::Event &event)
{
    m_player.handle_event(event);
}

void World::update(double dt)
{
    m_background.update(dt);
    m_player.update(dt);
    handle_player_collision();

    m_context.view->setCenter(m_player.get_center());
}

void World::draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_background);
    window.draw(m_tile_map);
    window.draw(m_player);

    sf::RectangleShape rect;
    rect.setSize({m_player.get_rectangle().width, m_player.get_rectangle().height});
    rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(m_player.get_center());
    window.draw(rect);
}

void World::handle_player_collision()
{
    std::vector<std::pair<uint32_t, sf::FloatRect>> colliding_rectangles;
    const auto& map_tiles = m_tile_map.get_colliders();
    sf::Vector2f velocity = m_player.get_velocity();

    auto get_colliding_rectangles_indexes = [&] () {
        std::vector<std::pair<uint32_t, sf::FloatRect>> rects;

        for (int i = 0; i < map_tiles.size(); ++i)
        {
            sf::FloatRect l_rect;

            if (m_player.get_rectangle().intersects(map_tiles.at(i), l_rect))
                rects.emplace_back(i, std::move(l_rect));
        }

        return rects;
    };

    if (velocity.x != 0)
    {
        m_player.move(velocity.x, 0);

        colliding_rectangles = get_colliding_rectangles_indexes();

        if (!colliding_rectangles.empty())
        {
            std::sort(colliding_rectangles.begin(), colliding_rectangles.end(),
                      [] (const std::pair<uint32_t, sf::FloatRect>& a, const std::pair<uint32_t, sf::FloatRect>& b) {
                          return a.second.width > b.second.width;
            });

            uint32_t highest_overlapping_rect_index = colliding_rectangles.front().first;

            if (velocity.x > 0)
            {
                float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().x - m_player.get_rectangle().width;
                m_player.setPosition(new_pos, m_player.getPosition().y);
            }
            else
            {
                float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().x + map_tiles.at(highest_overlapping_rect_index).width;
                m_player.setPosition(new_pos, m_player.getPosition().y);
            }
        }
    }

    if (velocity.y != 0)
    {
        m_player.move(0, velocity.y);
        colliding_rectangles = get_colliding_rectangles_indexes();

        if (!colliding_rectangles.empty())
        {
            std::sort(colliding_rectangles.begin(), colliding_rectangles.end(),
                      [] (const std::pair<uint32_t, sf::FloatRect>& a, const std::pair<uint32_t, sf::FloatRect>& b) {
                          return a.second.height > b.second.height;
                      });

            uint32_t highest_overlapping_rect_index = colliding_rectangles.front().first;

            if (velocity.y > 0)
            {
                float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().y - m_player.get_rectangle().height;
                m_player.setPosition(m_player.getPosition().x, new_pos);
            }
            else
            {
                float new_pos = map_tiles.at(highest_overlapping_rect_index).getPosition().y + map_tiles.at(highest_overlapping_rect_index).height;
                m_player.setPosition(m_player.getPosition().x, new_pos);
            }
        }
    }
}
