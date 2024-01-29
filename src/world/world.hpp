//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_WORLD_HPP
#define PLATFORMER_WORLD_HPP

#include <memory>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include "back_ground.hpp"
#include "player/player.hpp"
#include "collision.hpp"
#include "tiled_json_loader.hpp"
#include "enemies/spike.hpp"
#include "camera.hpp"

#include <thread>

class World
{
public:
    World(GameContext& context);

    void handle_events(const sf::Event& event);
    void update(double dt);
    void draw();

private:
    void setup_spikes(const nlohmann::json& spike_pos_layer);

private:
    GameContext& m_context;
    sf::Sprite background_map;
    BackGround m_background;
    Player m_player;
    std::vector<sf::Rect<float>> m_solid_tiles;
    std::vector<Spike> spikes;
};


#endif //PLATFORMER_WORLD_HPP
