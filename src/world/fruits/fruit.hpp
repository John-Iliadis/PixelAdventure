//
// Created by Gianni on 4/02/2024.
//

#ifndef PLATFORMER_FRUIT_HPP
#define PLATFORMER_FRUIT_HPP

#include "../../animation/animation.hpp"
#include "../sprite_collider.hpp"


class Fruit : public sf::Drawable
{
public:
    Fruit(const sf::Texture& texture, const sf::Vector2f& position);

    void update(double dt);

    sf::Rect<float> get_collider() const;
    sf::Vector2f get_position() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    SpriteCollider m_fruit;
    Animation m_animation;
};


#endif //PLATFORMER_FRUIT_HPP
