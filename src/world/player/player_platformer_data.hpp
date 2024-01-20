//
// Created by Gianni on 19/01/2024.
//

#ifndef PLATFORMER_PLAYER_PLATFORMER_DATA_HPP
#define PLATFORMER_PLAYER_PLATFORMER_DATA_HPP

#include <fstream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include "../../vendor/json.hpp"
#include "../../utilities/utils.hpp"


struct PlatformerData
{
    sf::RectangleShape collision_rect;
    sf::Vector2f velocity;
    float move_speed;
    float gravity;
    float gravity_speed;
    float wall_sliding_speed;
    float jump_speed;
    float jump_pressed_remember_time;
    bool previously_jumped;
    bool previously_double_jumped;
    bool facing_right;
    bool touching_wall;
    sf::Clock time_since_last_jump_button_pressed;

    PlatformerData()
    {
        std::ifstream file("../data/player/platformer_data.json");

        if (!file.is_open())
            throw std::runtime_error("PlatformerData::load_platformer_data - Failed to open file\n");

        nlohmann::json json = nlohmann::json::parse(file);

        collision_rect.setFillColor(sf::Color::Transparent);
        collision_rect.setSize({json["collision_rect"]["width"].get<float>(),
                                json["collision_rect"]["height"].get<float>()});
        collision_rect.setScale(2, 2);
        set_origin_mid_bottom(collision_rect);

        move_speed = json["move_speed"].get<float>();
        gravity_speed = json["gravity_speed"].get<float>();
        gravity = gravity_speed;
        wall_sliding_speed = json["wall_sliding_speed"].get<float>();
        jump_speed = json["jump_speed"].get<float>();
        jump_pressed_remember_time = json["jump_pressed_remember_time"].get<float>();
        facing_right = json["facing_right"].get<bool>();

        previously_jumped = false;
        previously_double_jumped = false;
        touching_wall = false;

        file.close();
    }
};


#endif //PLATFORMER_PLAYER_PLATFORMER_DATA_HPP
