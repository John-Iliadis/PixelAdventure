//
// Created by Gianni on 1/02/2024.
//

#include "chain_saw.hpp"


ChainSaw::ChainSaw(TextureManager &textures)
    : Saw(textures.get("saw_on"))
    , m_duration()
    , m_ellapsed()
{
    sf::Texture& chain_texture = textures.get("saw_chain");
    chain_texture.setRepeated(true);

    m_chain.setTexture(chain_texture);
    m_chain.setOrigin(0, m_chain.getGlobalBounds().height / 2);
}

void ChainSaw::update(double dt)
{
    Saw::update(dt);

    m_ellapsed += dt;

    float t = m_ellapsed / m_duration;

    assert(!std::isinf(t));

    if (t > 1.f) t = 1.f;

    float easing = t < 0.5 ? 4 * std::pow(t, 3) : 1 - std::pow(-2 * t + 2, 3) / 2;

    sf::Vector2f new_pos = m_start_pos + (m_target_pos - m_start_pos) * easing;

    m_sprite_collider.set_position(new_pos);

    if (new_pos == m_target_pos)
    {
        m_ellapsed = 0;
        m_target_pos = m_start_pos;
        m_start_pos = new_pos;
    }
}

void ChainSaw::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_chain);
    target.draw(m_sprite_collider);
}

void ChainSaw::set_path(const LinePath &path)
{
    m_path = path;

    m_start_pos = m_path.starting_point;
    m_target_pos = m_path.end_point;

    m_sprite_collider.set_position(m_path.starting_point);

    sf::Rect<int> chain_texture_rect {
        0, 0,
        static_cast<int>(m_path.get_distance()),
        static_cast<int>(m_chain.getGlobalBounds().height)
    };

    m_chain.setTextureRect(chain_texture_rect);
    m_chain.setPosition(m_path.starting_point);

    if (std::isinf(m_path.get_slope()))
        m_chain.rotate(90);

    m_duration = 128 / m_path.get_distance();
}
