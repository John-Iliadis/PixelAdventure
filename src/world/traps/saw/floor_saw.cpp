//
// Created by Gianni on 1/02/2024.
//

#include "floor_saw.hpp"


const float FloorSaw::speed = 180;

FloorSaw::FloorSaw(const TextureManager& textures)
    : Saw(textures.get("saw_on"))
    , m_current_target_index()
{
}

void FloorSaw::update(double dt)
{
    Saw::update(dt);

    sf::Vector2f target = m_path.at(m_current_target_index);
    sf::Vector2f direction = target - m_sprite_collider.get_position();
    float distance = std::hypot(direction.x, direction.y);

    if (distance > speed * dt)
    {
        direction /= distance;
        m_sprite_collider.move(direction * speed * static_cast<float>(dt));
    }
    else
    {
        m_sprite_collider.set_position(target);
        m_current_target_index = (m_current_target_index + 1) % m_path.size();
    }
}

void FloorSaw::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite_collider);
}

void FloorSaw::set_path(std::vector<sf::Vector2f>&& path)
{
    m_path = std::move(path);
}

void FloorSaw::set_current_pos_index(uint8_t index)
{
    assert(!m_path.empty());

    m_sprite_collider.set_position(m_path.at(index));
    m_current_target_index = (index + 1) % m_path.size();
}
