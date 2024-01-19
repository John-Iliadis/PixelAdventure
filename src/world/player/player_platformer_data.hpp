//
// Created by Gianni on 19/01/2024.
//

#ifndef PLATFORMER_PLAYER_PLATFORMER_DATA_HPP
#define PLATFORMER_PLAYER_PLATFORMER_DATA_HPP

#include <fstream>
#include <SFML/System/Vector2.hpp>
#include "../../vendor/json.hpp"


struct PlatformerData
{
    sf::Vector2f velocity;
    float move_speed = 0;
    float gravity = 0;
    float jump_speed;
    bool previously_jumped = false;
    bool previously_double_jumped = false;
    bool facing_right = true;

    void load_platformer_data(const std::string& file_name)
    {
        std::ifstream file(file_name);

        if (!file.is_open())
            throw std::runtime_error("PlatformerData::load_platformer_data - Failed to open file " + file_name);

        nlohmann::json json = nlohmann::json::parse(file);

        move_speed = json["move_speed"].get<float>();
        gravity = json["gravity"].get<float>();
        jump_speed = json["jump_speed"].get<float>();
        facing_right = json["facing_right"].get<bool>();

        file.close();
    }
};

#endif //PLATFORMER_PLAYER_PLATFORMER_DATA_HPP
