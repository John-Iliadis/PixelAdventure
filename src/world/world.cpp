//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"

static bool following_player = true;

World::World(GameContext& context)
    : m_context(context)
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

    setup_spikes(TiledJsonLoader::get_layer(map_data, "spike_positions"));
}

void World::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::M && following_player)
        {
            following_player = false;
            m_player.set_accepting_input(false);
            m_context.camera->set_target({1000, 1000}, [this] () {m_player.set_accepting_input(true); following_player = true;});
        }
    }

    m_player.handle_events(event);
}

void World::update(double dt)
{
    m_background.update(dt);
    m_player.update(dt);

    if (following_player)
        m_context.camera->set_center(m_player.get_center());
}

void World::draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_background);
    window.draw(background_map);
    window.draw(m_player);
}


void World::setup_spikes(const nlohmann::json &spike_pos_layer)
{
    for (const auto& object : spike_pos_layer["objects"])
    {
        int rotation = object["properties"][0]["value"].get<int>();
        sf::Vector2f position {
            object["x"].get<float>(),
            object["y"].get<float>()
        };

        spikes.emplace_back(
                m_context.texture_manager->get("spike"),
                position,
                rotation
                );
    }
}
