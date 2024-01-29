//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"


World::World(GameContext& context)
    : m_context(context)
  //  , m_tile_map("../data/tmx/test_map3.tmj")
    , m_player(context)
    , m_background(*m_context.texture_manager, m_context.window->getSize()) // todo: fix background texture size
{
    std::ifstream file("../data/tmx/test_map3.tmj");

    if (!file.is_open())
        throw std::runtime_error("World::World: Failed to open file");

    nlohmann::json map_data = nlohmann::json::parse(file);

    file.close();

    m_solid_tiles = TiledJsonLoader::get_tiles(map_data, "solid_tiles");

    auto player_pos = TiledJsonLoader::get_position(map_data, "spawn_positions", "player_spawn_pos");

    m_player.set_position(player_pos);
    m_player.set_collision_callback([this] (double dt) {
        Collision::handle_x_axis_collisions(m_player, m_solid_tiles, dt);
        Collision::handle_y_axis_collisions(m_player, m_solid_tiles, dt);
    });

    background_map.setTexture(m_context.texture_manager->get("test_map3"));
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
    window.draw(background_map);
    window.draw(m_player);
}
