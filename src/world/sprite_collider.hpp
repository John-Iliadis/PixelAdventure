//
// Created by Gianni on 22/01/2024.
//

#ifndef PLATFORMER_SPRITE_COLLIDER_HPP
#define PLATFORMER_SPRITE_COLLIDER_HPP

#include <cstdint>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../utilities/utils.hpp"
#include "enums.hpp"


class SpriteCollider : public sf::Drawable, public sf::Transformable
{
public:
    SpriteCollider();

    void set_texture(const sf::Texture& texture); // todo: if new texture is different size, new origin has to be set
    void set_texture_rect(const sf::IntRect& rect);
    void set_hitbox_size(float width, float height);
    void set_orientation(SpriteOrientation orientation);

    void set_origin_center();
    void set_origin_mid_bottom();

    sf::Vector2f get_sprite_center() const;
    sf::FloatRect get_hitbox() const;
    SpriteOrientation get_orientation() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
    sf::RectangleShape m_hit_box;
    SpriteOrientation m_orientation;
};


#endif //PLATFORMER_SPRITE_COLLIDER_HPP
