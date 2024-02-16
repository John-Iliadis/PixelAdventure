//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_WORLD_HPP
#define PLATFORMER_WORLD_HPP

#include <memory>
#include <fstream>
#include <SFML/Window/Event.hpp>
#include "../structs/level_details.hpp"
#include "../camera/camera.hpp"
#include "../scrolling_background/scrolling_background.hpp"
#include "player/player.hpp"
#include "collision.hpp"
#include "tiled_json_loader.hpp"
#include "traps/spikes/spike.hpp"
#include "checkpoint/checkpoint_manager.hpp"
#include "particles/death_particle_system.hpp"
#include "traps/saw/chain_saw.hpp"
#include "traps/saw/floor_saw.hpp"
#include "traps/trap_manager.hpp"
#include "traps/fire_trap/fire_trap.hpp"
#include "traps/spike_head/spike_head.hpp"
#include "traps/spiked_ball/pendulum_spiked_ball.hpp"
#include "traps/spiked_ball/circular_spiked_ball.hpp"
#include "fruits/fruit_manager.hpp"
#include "finish_cup.hpp"


class World
{
public:
    World(GameContext& context, const LevelDetails& level_details);

    void handle_events(const sf::Event& event);
    void update(double dt);
    void draw();

    bool game_over() const;

private:
    void setup_player(const nlohmann::json& map_data);
    void setup_checkpoints(const nlohmann::json& checkpoint_pos_layer);
    void setup_spikes(const nlohmann::json& spike_pos_layer);
    void setup_fire_traps(const nlohmann::json& fire_trap_layer);
    void setup_saw_traps(const nlohmann::json& saw_trap_layer);
    void setup_spike_head_traps(const nlohmann::json& spike_head_layer);
    void setup_spiked_balls(const nlohmann::json& spiked_ball_layer);
    void setup_finish(const nlohmann::json& finish_layer);

private:
    GameContext& m_context;
    ScrollingBackground m_scrolling_background;
    sf::Sprite m_map;
    Player m_player;
    CheckpointManager m_checkpoint_manager;
    TrapManager m_trap_manager;
    FruitManager m_fruit_manager;
    DeathParticleSystem m_death_particles;
    FinishCup m_finish;
    std::vector<sf::Rect<float>> m_solid_tiles;
};


#endif //PLATFORMER_WORLD_HPP
