//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_SAW_HPP
#define PLATFORMER_SAW_HPP

#include "../../sprite_collider.hpp"
#include "../../../animation/animation.hpp"


class Saw : public sf::Drawable
{
public:
    Saw(const sf::Texture& texture);
    virtual ~Saw() = default;

    virtual void update(double dt);

    sf::Rect<float> get_collider() const;

protected:
    Animation m_animation;
    SpriteCollider m_sprite_collider;
};


#endif //PLATFORMER_SAW_HPP
