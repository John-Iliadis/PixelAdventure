//
// Created by Gianni on 12/02/2024.
//

#ifndef PLATFORMER_SETTINGS_HPP
#define PLATFORMER_SETTINGS_HPP

#include <fstream>
#include "../vendor/json.hpp"


struct Settings
{
    float music_volume;
    float sound_volume;
    std::unordered_map<std::string, std::string> action_map;

    void load_from_file(const std::string& filename)
    {
        std::ifstream file(filename);

        assert(file.is_open());

        auto json = nlohmann::json::parse(file);

        file.close();

        music_volume = json["music_volume"].get<float>();
        sound_volume = json["sound_volume"].get<float>();
        action_map["move_left_action"] = json["move_left_action"].get<std::string>();
        action_map["move_right_action"] = json["move_right_action"].get<std::string>();
        action_map["jump_action"] = json["jump_action"].get<std::string>();
    }

    void save_to_file(const std::string& filename)
    {
        std::ofstream file(filename, std::ios::trunc);

        assert(file.is_open());

        nlohmann::json settings {
                {"music_volume", music_volume},
                {"sound_volume", sound_volume},
                {"move_left_action", action_map["move_left_action"]},
                {"move_right_action", action_map["move_right_action"]},
                {"jump_action", action_map["jump_action"]}
        };

        file << settings.dump(4);

        file.close();
    }
};

#endif //PLATFORMER_SETTINGS_HPP
