//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_BACK_GROUND_HPP
#define PLATFORMER_BACK_GROUND_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../asset_managers/texture_manager.hpp"


class BackGround : public sf::Drawable
{
public:
    BackGround(TextureManager& texture_manager, const sf::Vector2u& map_texture_height);
    void update(double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_map;
    sf::Sprite m_scrollable_background[2];
    const float m_scroll_speed;
};


#endif //PLATFORMER_BACK_GROUND_HPP
