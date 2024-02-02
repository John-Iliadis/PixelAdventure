//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_SAW_HPP
#define PLATFORMER_SAW_HPP

#include "../../../animation/animation.hpp"
#include "../../sprite_collider.hpp"
#include "../trap.hpp"


class Saw : public Trap
{
public:
    Saw(const sf::Texture& texture);
    virtual ~Saw() = default;

    void update(double dt) override;

    sf::Rect<float> get_collider() const override;

protected:
    Animation m_animation;
    SpriteCollider m_sprite_collider;
};


#endif //PLATFORMER_SAW_HPP
