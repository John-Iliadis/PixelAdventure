//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"


World::World(GameContext& context)
    : m_context(context)
    , m_player(context)
    , m_background(*m_context.texture_manager)
    , m_death_articles(*m_context.texture_manager)
{
    std::ifstream file("../data/tmx/test_map3.tmj");

    if (!file.is_open())
        throw std::runtime_error("World::World: Failed to open file");

    nlohmann::json map_data = nlohmann::json::parse(file);

    file.close();

    m_solid_tiles = TiledJsonLoader::get_tiles(map_data, "solid_tiles");

    auto player_pos = TiledJsonLoader::get_position(map_data, "spawn_positions", "player_spawn_pos");

    m_player.set_position(player_pos);
    m_player.set_respawn_position(player_pos);

    m_player.set_collision_callback([this] (double dt) {
        Collision::handle_x_axis_collisions(m_player, m_solid_tiles, dt);
        Collision::handle_y_axis_collisions(m_player, m_solid_tiles, dt);
    });

    m_player.set_death_particle_callback([this] () {
        m_death_articles.add_particle(ParticleType::PLAYER_DEATH, m_player.get_position(), {m_player.get_velocity().x, -400}, m_player.get_orientation());
    });

    m_player.set_camera_transition_callback([this] () {
        sf::Vector2f player_respawn_pos = m_player.get_respawn_pos();
        sf::Vector2f camera_target(player_respawn_pos.x, player_respawn_pos.y - m_player.get_sprite_size().height / 2.f);
        m_context.camera->set_target(camera_target, 1.2, [this] () {m_player.respawn();});
    });

    setup_checkpoints(TiledJsonLoader::get_layer(map_data, "checkpoint_positions"));
    setup_spikes(TiledJsonLoader::get_layer(map_data, "spike_positions"));
    setup_fire_traps(TiledJsonLoader::get_layer(map_data, "fire_trap_positions"));
}

void World::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            m_death_articles.add_particle(ParticleType::PLAYER_DEATH, m_player.get_position(), {m_player.get_velocity().x, -400}, m_player.get_orientation());
        }
        else if (event.key.code == sf::Keyboard::R)
        {
            m_player.respawn();
        }
    }

    m_player.handle_events(event);
}

void World::update(double dt)
{
    m_background.update(dt);
    m_player.update(dt);
    m_checkpoint_manager.update(m_player, dt);
    m_death_articles.update(dt);
    m_fire_trap_manager.update(m_player, dt);

    m_spike_manager.handle_collisions(m_player);

    if (m_player.is_alive())
        m_context.camera->set_center(m_player.get_center());
}

void World::draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_background);
    window.draw(m_checkpoint_manager);
    window.draw(m_player);
    window.draw(m_spike_manager);
    window.draw(m_death_articles);
    window.draw(m_fire_trap_manager);
}

void World::setup_spikes(const nlohmann::json &spike_pos_layer)
{
    static Spike prototype(m_context.texture_manager->get("spike"));

    for (const auto& object : spike_pos_layer["objects"])
    {
        int rotation = TiledJsonLoader::get_property<int>(object["properties"], "rotation");

        sf::Vector2f position {
            object["x"].get<float>(),
            object["y"].get<float>()
        };

        Spike l_spike = prototype;

        l_spike.place(position, rotation);

        m_spike_manager.push_back(std::move(l_spike));
    }
}

void World::setup_checkpoints(const nlohmann::json &checkpoint_pos_layer)
{
    static Checkpoint prototype(*m_context.texture_manager);

    for (const auto& object : checkpoint_pos_layer["objects"])
    {
        sf::Vector2f pos {
            object["x"].get<float>(),
            object["y"].get<float>()
        };

        Checkpoint l_checkpoint = prototype;
        l_checkpoint.set_position(pos);

        m_checkpoint_manager.push_back(std::move(l_checkpoint));
    }
}

void World::setup_fire_traps(const nlohmann::json &fire_trap_layer)
{
    static FireTrap prototype(*m_context.texture_manager);

    for (const auto& object : fire_trap_layer["objects"])
    {
        sf::Vector2f pos {
            object["x"].get<float>(),
            object["y"].get<float>()
        };

        int rotation = TiledJsonLoader::get_property<int>(object["properties"], "rotation");
        float on_time = TiledJsonLoader::get_property<float>(object["properties"], "on_time");
        float off_time = TiledJsonLoader::get_property<float>(object["properties"], "off_time");

        FireTrap l_fire_trap = prototype;
        l_fire_trap.place(pos, rotation);
        l_fire_trap.set_timer(on_time, off_time);

        m_fire_trap_manager.push_back(std::move(l_fire_trap));
    }
}
