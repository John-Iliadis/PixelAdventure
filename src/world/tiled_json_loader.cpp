//
// Created by Gianni on 29/01/2024.
//

#include "tiled_json_loader.hpp"

namespace TiledJsonLoader
{
    MapData get_map_data(const nlohmann::json& json_data)
    {
        MapData map_data{};

        map_data.tile_width = json_data["tilewidth"].get<uint32_t>();
        map_data.tile_height = json_data["tileheight"].get<uint32_t>();
        map_data.total_tiles_x = json_data["width"].get<uint32_t>();
        map_data.total_tiles_y = json_data["height"].get<uint32_t>();

        return map_data;
    }

    nlohmann::json get_list_object(const nlohmann::json& list, const std::string& object_name)
    {
        auto itr = std::find_if(list.begin(), list.end(),
                                [&object_name] (const nlohmann::json& object) {
                                    return (object["name"].get<std::string>() == object_name);
                                });

        assert(itr != list.end());

        return *itr;
    }

    std::vector<sf::Rect<float>> get_tiles(const nlohmann::json& json_data, const std::string& layer_name)
    {
        std::vector<sf::Rect<float>> tiles;

        MapData map_data = get_map_data(json_data);

        std::vector<int> layer_data = get_list_object(json_data["layers"], layer_name)["data"].get<std::vector<int>>();

        for (int i = 0; i < map_data.total_tiles_y; ++i)
        {
            for (int j = 0; j < map_data.total_tiles_x; ++j)
            {
                if (layer_data.at(i * map_data.total_tiles_x + j) != 0)
                {
                    sf::Rect<float> tile_rect {
                        static_cast<float>(j * map_data.tile_width),
                        static_cast<float>(i * map_data.tile_height),
                        static_cast<float>(map_data.tile_width),
                        static_cast<float>(map_data.tile_height)
                    };

                    tiles.push_back(std::move(tile_rect));
                }
            }
        }

        return tiles;
    }

    sf::Vector2f get_position(const nlohmann::json& json_data, const std::string& layer_name, const std::string& pos_name)
    {
        nlohmann::json objects = get_list_object(json_data["layers"], layer_name)["objects"];

        auto itr = std::find_if(objects.begin(), objects.end(),
            [&pos_name] (const nlohmann::json& object) {
                return (object["name"].get<std::string>() == pos_name);
        });

        assert(itr != objects.end());

        return {
                (*itr)["x"].get<float>(),
                (*itr)["y"].get<float>()
        };
    }
}
