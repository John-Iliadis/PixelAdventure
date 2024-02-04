//
// Created by Gianni on 3/02/2024.
//

#include "spiked_ball.hpp"


static const sf::Vector2f collider_size = {14, 14};

SpikedBall::SpikedBall(TextureManager &textures)
    : m_angle()
    , m_length()
    , m_angular_velocity()
{
    m_spiked_ball.set_texture(textures.get("spiked_ball"));
    m_spiked_ball.set_collider_size(collider_size);
    m_spiked_ball.set_origin(Origin::CENTER);

    m_base.setTexture(textures.get("spiked_ball_base"));
    utils::set_origin(m_base, Origin::CENTER);

    sf::Texture& chain_texture = textures.get("spiked_ball_chain");
    chain_texture.setRepeated(true);

    m_chain.setTexture(chain_texture);
    m_chain.setOrigin(0, chain_texture.getSize().y / 2.f);
}

sf::FloatRect SpikedBall::get_collider() const
{
    return m_spiked_ball.get_collider();
}

void SpikedBall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_chain);
    target.draw(m_base);
    target.draw(m_spiked_ball);
}
