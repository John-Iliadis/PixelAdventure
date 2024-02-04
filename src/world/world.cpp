//
// Created by Gianni on 13/01/2024.
//

#include "world.hpp"


World::World(GameContext& context, const LevelDetails& level_details)
    : m_context(context)
    , m_player(context)
    , m_death_particles(*m_context.texture_manager)
{
    const sf::Texture& map_texture = m_context.texture_manager->get(level_details.map_texture_id);
    m_map.setTexture(map_texture);

    sf::Texture& scrolling_bg_texture = m_context.texture_manager->get(level_details.scrolling_background_texture_id);
    sf::Vector2i map_size = static_cast<sf::Vector2i>(map_texture.getSize());
    m_scrolling_background = ScrollingBackground(scrolling_bg_texture, map_size);

    std::ifstream file(level_details.json_file_name);
    assert(file.is_open());

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
        m_death_particles.add_particle(ParticleType::PLAYER_DEATH, m_player.get_position(), {m_player.get_velocity().x, -400}, m_player.get_orientation());
    });

    m_player.set_camera_transition_callback([this] () {
        sf::Vector2f player_respawn_pos = m_player.get_respawn_pos();
        sf::Vector2f camera_target(player_respawn_pos.x, player_respawn_pos.y - m_player.get_sprite_size().height / 2.f);
        m_context.camera->set_target(camera_target, 1.2, [this] () {m_player.respawn();});
    });

    m_player.set_move_camera_callback([this] () {
        if (m_player.is_alive()) m_context.camera->set_center(m_player.get_center());
    });

    m_fruit_manager = FruitManager(TiledJsonLoader::get_list_object(map_data["layers"], "fruit_layer"), *m_context.texture_manager);

    setup_checkpoints(TiledJsonLoader::get_list_object(map_data["layers"], "checkpoint_positions"));
    setup_spikes(TiledJsonLoader::get_list_object(map_data["layers"], "spike_positions"));
    setup_fire_traps(TiledJsonLoader::get_list_object(map_data["layers"], "fire_trap_positions"));
    setup_saw_traps(TiledJsonLoader::get_list_object(map_data["layers"], "saw_layer"));
    setup_spike_head_traps(TiledJsonLoader::get_list_object(map_data["layers"], "spike_head_layer"));
    setup_spiked_balls(TiledJsonLoader::get_list_object(map_data["layers"], "spiked_ball_layer"));
}

void World::handle_events(const sf::Event &event)
{
    m_player.handle_events(event);
}

void World::update(double dt)
{
    m_scrolling_background.update(dt);
    m_player.update(dt);
    m_checkpoint_manager.update(m_player, dt);
    m_trap_manager.update(m_player, dt);
    m_fruit_manager.update(m_player, dt);
    m_death_particles.update(dt);
}

void World::draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_scrolling_background);
    window.draw(m_trap_manager);
    window.draw(m_map);
    window.draw(m_checkpoint_manager);
    window.draw(m_fruit_manager);
    window.draw(m_player);
    window.draw(m_death_particles);
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

        auto l_spike = std::make_unique<Spike>(prototype);

        l_spike->place(position, rotation);

        m_trap_manager.push_back(std::move(l_spike));
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

        auto l_fire_trap = std::make_unique<FireTrap>(prototype);

        l_fire_trap->place(pos, rotation);
        l_fire_trap->set_timer(on_time, off_time);

        m_trap_manager.push_back(std::move(l_fire_trap));
    }
}

void World::setup_saw_traps(const nlohmann::json &saw_trap_layer)
{
    static ChainSaw chain_saw_prototype(*m_context.texture_manager);
    static FloorSaw floor_saw_prototype(*m_context.texture_manager);

    for (const auto& sub_layer : saw_trap_layer["layers"])
    {
        if (sub_layer["name"] == "chain_saw")
        {
            auto l_chain_saw = std::make_unique<ChainSaw>(chain_saw_prototype);

            std::unordered_map<std::string, sf::Vector2f> positions;

            for (const auto& object : sub_layer["objects"])
            {
                positions[object["name"].get<std::string>()] = {
                        object["x"].get<float>(),
                        object["y"].get<float>()
                };
            }

            LinePath line_path {
                positions.at("start"),
                positions.at("finish"),
            };

            l_chain_saw->set_path(line_path);

            m_trap_manager.push_back(std::move(l_chain_saw));
        }
        else if (sub_layer["name"] == "floor_saw")
        {
            auto l_floor_saw = std::make_unique<FloorSaw>(floor_saw_prototype);

            std::vector<sf::Vector2f> path;
            uint8_t spawn_pos{};

            for (const auto& object : sub_layer["objects"])
            {
                sf::Vector2f l_position {
                    object["x"].get<float>(),
                    object["y"].get<float>()
                };

                path.push_back(std::move(l_position));

                if (object["name"] == "spawn_pos")
                    spawn_pos = path.size() - 1;
            }

            l_floor_saw->set_path(std::move(path));
            l_floor_saw->set_current_pos_index(spawn_pos);

            m_trap_manager.push_back(std::move(l_floor_saw));
        }
        else
        {
            assert(false);
        }
    }
}

void World::setup_spike_head_traps(const nlohmann::json& spike_head_layer)
{
    static SpikeHead spike_head_prototype(*m_context.texture_manager);

    for (const auto& sub_layer : spike_head_layer["layers"])
    {
        auto l_spike_head = std::make_unique<SpikeHead>(spike_head_prototype);

        std::vector<sf::Vector2f> path;
        uint8_t spawn_pos{};

        for (const auto& object : sub_layer["objects"])
        {
            sf::Vector2f l_position {
                object["x"].get<float>() + object["width"].get<float>() / 2.f,
                object["y"].get<float>() + object["height"].get<float>() / 2.f
            };

            path.push_back(std::move(l_position));

            if (object["name"] == "spawn_pos")
                spawn_pos = path.size() - 1;
        }

        l_spike_head->set_path(std::move(path));
        l_spike_head->set_spawn_pos_index(spawn_pos);

        m_trap_manager.push_back(std::move(l_spike_head));
    }
}

void World::setup_spiked_balls(const nlohmann::json& spiked_ball_layer)
{
    static PendulumSpikedBall pendulum_spiked_ball_prototype(*m_context.texture_manager);
    static CircularSpikedBall circular_spiked_ball_prototype(*m_context.texture_manager);

    for (const auto& sub_layer : spiked_ball_layer["layers"])
    {
        auto base = TiledJsonLoader::get_list_object(sub_layer["objects"], "base");
        auto bob = TiledJsonLoader::get_list_object(sub_layer["objects"], "bob");

        sf::Vector2f base_position {
            base["x"].get<float>() + base["width"].get<float>() / 2.f,
            base["y"].get<float>() + base["height"].get<float>() / 2.f
        };

        sf::Vector2f bob_position {
            bob["x"].get<float>() + bob["width"].get<float>() / 2.f,
            bob["y"].get<float>() + bob["height"].get<float>() / 2.f
        };

        float length = utils::get_distance(base_position, bob_position);

        if (sub_layer["name"] == "pendulum")
        {
            auto l_pendulum_spiked_ball = std::make_unique<PendulumSpikedBall>(pendulum_spiked_ball_prototype);

            l_pendulum_spiked_ball->place(base_position, length);

            m_trap_manager.push_back(std::move(l_pendulum_spiked_ball));
        }
        else if (sub_layer["name"] == "circular")
        {
            auto l_circular_spiked_ball = std::make_unique<CircularSpikedBall>(circular_spiked_ball_prototype);

            l_circular_spiked_ball->place(base_position, length);

            m_trap_manager.push_back(std::move(l_circular_spiked_ball));
        }
        else
        {
            assert(false);
        }
    }
}
