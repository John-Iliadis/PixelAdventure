//
// Created by Gianni on 29/01/2024.
//

#ifndef PLATFORMER_SPIKE_HPP
#define PLATFORMER_SPIKE_HPP

#include <stdexcept>
#include <cstdint>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../trap.hpp"
#include "../../sprite_collider.hpp"


class Spike : public Trap
{
public:
    Spike() = default;
    Spike(const sf::Texture& texture);

    void place(const sf::Vector2f& pos, int rotation);

    void update(double dt) override;

    sf::Rect<float> get_collider() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    SpriteCollider m_sprite_collider;
};


#endif //PLATFORMER_SPIKE_HPP
