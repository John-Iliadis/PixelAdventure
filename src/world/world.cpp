//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"


World::World(GameContext& context)
    : m_context(context)
    , m_tile_map("../data/tmx/test_map3.tmj")
    , m_background(*m_context.texture_manager, m_context.window->getSize()) // todo: fix background texture size
{
    m_player.set_position(m_tile_map.get_player_spawn_pos());
    m_player.set_collision_callback([this] (double dt) {
        Collision::handle_x_axis_collisions(m_player, m_tile_map, dt);
        Collision::handle_y_axis_collisions(m_player, m_tile_map, dt);
    });
}

void World::handle_events(const sf::Event &event)
{
    m_player.handle_events(event);
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
}
