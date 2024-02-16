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
   // m_chain.setOrigin(0, m_chain.getGlobalBounds().height / 2);
}

void ChainSaw::update(double dt)
{
    Saw::update(dt);

    m_ellapsed += dt;

    float t = m_ellapsed / m_duration;

    assert(!std::isinf(t));

    float easing = easing_functions::ease_in_out_cubic(t);

    sf::Vector2f new_pos = m_start_pos + (m_target_pos - m_start_pos) * easing;

    m_sprite_collider.set_position(new_pos);

    if (new_pos == m_target_pos)
    {
        m_ellapsed = 0;
        std::swap(m_start_pos, m_target_pos);
    }
}

void ChainSaw::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_chain);
    target.draw(m_sprite_collider);
}

void ChainSaw::set_path(const LinePath &path)
{
    m_duration = 128 / path.get_distance();

    m_start_pos = path.starting_point;
    m_target_pos = path.end_point;

    m_sprite_collider.set_position(path.starting_point);

    sf::Rect<int> chain_texture_rect {
        0, 0,
        static_cast<int>(path.get_distance()),
        static_cast<int>(m_chain.getGlobalBounds().height)
    };

    Origin chain_origin;

    if (path.starting_point.y == path.end_point.y)
    {
        chain_origin = path.starting_point.x < path.end_point.x? Origin::CENTER_LEFT : Origin::CENTER_RIGHT;
    }
    else
    {
        chain_origin = path.starting_point.y < path.end_point.y? Origin::CENTER_LEFT : Origin::CENTER_RIGHT;
    }

    m_chain.setTextureRect(chain_texture_rect);
    m_chain.setPosition(path.starting_point);
    utils::set_origin(m_chain, chain_origin);

    if (std::isinf(path.get_slope()))
        m_chain.rotate(90);
}
