//
// Created by Gianni on 26/01/2024.
//

#ifndef PLATFORMER_PLAYER_DATA_HPP
#define PLATFORMER_PLAYER_DATA_HPP

#include <fstream>
#include <string>
#include <SFML/System/Vector2.hpp>
#include "../vendor/json.hpp"

struct PlayerData
{
    sf::Vector2f velocity;
    sf::Vector2f collider_size;
    sf::Vector2f respawn_position;
    float move_speed;
    float gravity;
    float gravity_speed;
    float wall_sliding_speed;
    float jump_speed;
    float jump_pressed_remember_time;
    float jump_pressed_ellapsed_time;
    bool previously_jumped;
    bool previously_double_jumped;
    bool touching_wall;
    bool alive;
    bool accepting_input;

    void load_from_file(const std::string& file_name)
    {
        std::ifstream file(file_name);

        if (!file.is_open())
            throw std::runtime_error("Player::init_platformer_data - Failed to open file " + file_name + '\n');

        nlohmann::json json = nlohmann::json::parse(file);

        file.close();

        collider_size = {json["hitbox"]["width"].get<float>(), json["hitbox"]["height"].get<float>()};
        move_speed = json["move_speed"].get<float>();
        gravity_speed = json["gravity_speed"].get<float>();
        gravity = gravity_speed;
        wall_sliding_speed = json["wall_sliding_speed"].get<float>();
        jump_speed = json["jump_speed"].get<float>();
        jump_pressed_remember_time = json["jump_pressed_remember_time"].get<float>();
        jump_pressed_ellapsed_time = 0;
        previously_jumped = false;
        previously_double_jumped = false;
        touching_wall = false;
        alive = true;
        accepting_input = true;
    }
};

#endif //PLATFORMER_PLAYER_DATA_HPP
