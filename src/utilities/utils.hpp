//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_UTILS_HPP
#define PLATFORMER_UTILS_HPP

#include <windows.h>
#include <cstdint>
#include <stdexcept>
#include <SFML/Graphics/Sprite.hpp>

uint32_t get_max_refresh_rate();

void set_origin_center(sf::Sprite& sprite);
void set_origin_top_left(sf::Sprite& sprite);
void flip_sprite_x(sf::Sprite& sprite, bool facing_right);

#endif //PLATFORMER_UTILS_HPP
