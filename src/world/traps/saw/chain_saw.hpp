//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_CHAIN_SAW_HPP
#define PLATFORMER_CHAIN_SAW_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "../../../asset_managers/texture_manager.hpp"
#include "../../../utilities/easing_functions.hpp"
#include "../../../utilities/utils.hpp"
#include "../../../structs/line_path.hpp"
#include "saw.hpp"


class ChainSaw : public Saw
{
public:
    ChainSaw(TextureManager& textures);

    void set_path(const LinePath& path);
    void update(double dt) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_chain;
    sf::Vector2f m_start_pos;
    sf::Vector2f m_target_pos;
    double m_duration;
    double m_ellapsed;
};


#endif //PLATFORMER_CHAIN_SAW_HPP
