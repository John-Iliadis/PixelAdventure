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
    std::vector<uint32_t> colliding_rectangles_indexes;
    const auto& map_tiles = m_tile_map.get_colliders();
    sf::Vector2f velocity = m_player.get_velocity();

    auto get_colliding_rectangles_indexes = [&] () {
        colliding_rectangles_indexes.clear();

        for (int i = 0; i < map_tiles.size(); ++i)
        {
            if (m_player.get_rectangle().intersects(map_tiles.at(i)))
                colliding_rectangles_indexes.push_back(i);
        }
    };

    if (velocity.x != 0)
    {
        m_player.move(velocity.x, 0);
        get_colliding_rectangles_indexes();

        auto highest_overlapping_rect_x = std::max_element(colliding_rectangles_indexes.begin(), colliding_rectangles_indexes.end(),
                                                           [&] (int a, int b) {
                if (velocity.x > 0)
                   return (map_tiles.at(a).getPosition().x - m_player.getPosition().x < map_tiles.at(b).getPosition().x - m_player.getPosition().x);
                else
                   return (map_tiles.at(a).getPosition().x + map_tiles.at(a).width - m_player.getPosition().x <
                           map_tiles.at(b).getPosition().x + map_tiles.at(b).width - m_player.getPosition().x);
        });

        if (highest_overlapping_rect_x != colliding_rectangles_indexes.end())
        {
            int i = *highest_overlapping_rect_x;

            if (velocity.x > 0)
            {
                m_player.setPosition(map_tiles.at(i).getPosition().x - m_player.get_rectangle().width, m_player.getPosition().y);
            }
            else if (velocity.x < 0)
            {
                m_player.setPosition(map_tiles.at(i).getPosition().x + map_tiles.at(i).width, m_player.getPosition().y);
            }
        }
    }

    if (velocity.y != 0)
    {
        m_player.move(0, velocity.y);
        get_colliding_rectangles_indexes();

        auto highest_overlapping_rect_y = std::max_element(colliding_rectangles_indexes.begin(), colliding_rectangles_indexes.end(),
                                                           [&] (int a, int b) {
                if (velocity.y > 0)
                   return (map_tiles.at(a).getPosition().y - m_player.getPosition().y < map_tiles.at(b).getPosition().y - m_player.getPosition().y);
                else
                   return (map_tiles.at(a).getPosition().y + map_tiles.at(a).height - m_player.getPosition().y <
                           map_tiles.at(b).getPosition().y + map_tiles.at(b).height - m_player.getPosition().y);
        });

        if (highest_overlapping_rect_y != colliding_rectangles_indexes.end())
        {
            int i = *highest_overlapping_rect_y;

            if (velocity.y > 0)
            {
                m_player.setPosition(m_player.getPosition().x, map_tiles.at(i).getPosition().y - m_player.get_rectangle().height);
            }
            else if (velocity.y < 0)
            {
                m_player.setPosition(m_player.getPosition().x, map_tiles.at(i).getPosition().y + map_tiles.at(i).height);
            }
        }
    }

//    for (uint32_t i : colliding_rectangles_indexes)
//    {
//        if (velocity.x > 0)
//        {
//            m_player.setPosition(map_tiles.at(i).getPosition().x - m_player.get_rectangle().width, m_player.getPosition().y);
//        }
//        else if (velocity.x < 0)
//        {
//            m_player.setPosition(map_tiles.at(i).getPosition().x + map_tiles.at(i).width, m_player.getPosition().y);
//        }
//    }

//    m_player.move(0, velocity.y);
//    get_colliding_rectangles_indexes();

//    for (uint32_t i : colliding_rectangles_indexes)
//    {
//        if (velocity.y > 0)
//        {
//            m_player.setPosition(m_player.getPosition().x, map_tiles.at(i).getPosition().y - m_player.get_rectangle().height);
//        }
//        else if (velocity.y < 0)
//        {
//            m_player.setPosition(m_player.getPosition().x, map_tiles.at(i).getPosition().y + map_tiles.at(i).height);
//        }
//    }
}
