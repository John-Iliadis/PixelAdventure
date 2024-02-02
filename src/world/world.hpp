//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_WORLD_HPP
#define PLATFORMER_WORLD_HPP

#include <memory>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include "background.hpp"
#include "player/player.hpp"
#include "collision.hpp"
#include "tiled_json_loader.hpp"
#include "traps/spikes/spike.hpp"
#include "camera.hpp"
#include "checkpoint/checkpoint_manager.hpp"
#include "particles/death_particle_system.hpp"
#include "traps/saw/chain_saw.hpp"
#include "traps/saw/floor_saw.hpp"
#include "traps/trap_manager.hpp"
#include "traps/fire_trap/fire_trap.hpp"


class World
{
public:
    World(GameContext& context);

    void handle_events(const sf::Event& event);
    void update(double dt);
    void draw();

private:
    void setup_checkpoints(const nlohmann::json& checkpoint_pos_layer);
    void setup_spikes(const nlohmann::json& spike_pos_layer);
    void setup_fire_traps(const nlohmann::json& fire_trap_layer);
    void setup_saw_traps(const nlohmann::json& saw_trap_layer);

private:
    GameContext& m_context;
    BackGround m_background;
    sf::Sprite m_map;
    Player m_player;
    CheckpointManager m_checkpoint_manager;
    TrapManager m_trap_manager;
    DeathParticleSystem m_death_articles;
    std::vector<sf::Rect<float>> m_solid_tiles;
};


#endif //PLATFORMER_WORLD_HPP
