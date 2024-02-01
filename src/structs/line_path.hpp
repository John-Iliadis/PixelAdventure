//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_LINE_PATH_HPP
#define PLATFORMER_LINE_PATH_HPP

#include <cmath>
#include <SFML/System/Vector2.hpp>


struct LinePath
{
    sf::Vector2f starting_point;
    sf::Vector2f end_point;

    sf::Vector2f get_vector() const
    {
        return {
                end_point.x - starting_point.x,
                end_point.y - starting_point.y
        };
    }

    float get_distance() const
    {
        float x = end_point.x - starting_point.x;
        float y = end_point.y - starting_point.y;

        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    float get_slope() const
    {
        float rise = end_point.y - starting_point.y;
        float run = end_point.x - starting_point.x;

        return rise / run;
    }
};

#endif //PLATFORMER_LINE_PATH_HPP
