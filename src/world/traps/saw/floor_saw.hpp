//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_FLOOR_SAW_HPP
#define PLATFORMER_FLOOR_SAW_HPP

#include "../../../asset_managers/texture_manager.hpp"
#include "saw.hpp"


class FloorSaw : public Saw
{
public:
    FloorSaw(const TextureManager& textures);

    void set_current_pos_index(uint8_t index);
    void set_path(std::vector<sf::Vector2f>&& path);

    void update(double dt) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<sf::Vector2f> m_path;
    uint8_t m_current_target_index;
    static const float speed;
};


#endif //PLATFORMER_FLOOR_SAW_HPP
