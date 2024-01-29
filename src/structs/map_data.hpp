//
// Created by Gianni on 29/01/2024.
//

#ifndef PLATFORMER_MAP_DATA_HPP
#define PLATFORMER_MAP_DATA_HPP

#include <cstdint>


struct MapData
{
    uint32_t tile_width;
    uint32_t tile_height;
    uint32_t total_tiles_x;
    uint32_t total_tiles_y;
};

#endif //PLATFORMER_MAP_DATA_HPP
