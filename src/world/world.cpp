//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"


World::World(GameContext& context)
    : m_context(context)
    , m_tile_map(m_context, "../data/tmx/test_map.tmj")
    , m_background(*m_context.texture_manager, m_context.window->getSize())
{
    m_player.set_collision_callbacks([this] (double dt) {Collision::handle_x_axis_collisions(m_player, m_tile_map, dt);},
                                     [this] (double dt) {Collision::handle_y_axis_collisions(m_player, m_tile_map, dt);});
}

void World::handle_events(const sf::Event &event)
{
    m_player.handle_event(event);
}

void World::update(double dt)
{
    m_background.update(dt);
    m_player.update(dt);

    m_context.view->setCenter(m_player.get_center());
}

void World::draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_background);
    window.draw(m_tile_map);
    window.draw(m_player);

//    sf::RectangleShape rect;
//    rect.setSize({m_player.get_rectangle().width, m_player.get_rectangle().height});
//    rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);
//    rect.setFillColor(sf::Color::Red);
//    rect.setPosition(m_player.get_center());
//    window.draw(rect);
}
