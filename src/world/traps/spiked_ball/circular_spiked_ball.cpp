//
// Created by Gianni on 3/02/2024.
//

#include "circular_spiked_ball.hpp"


CircularSpikedBall::CircularSpikedBall(TextureManager &texture_manager)
    : SpikedBall(texture_manager)
{
    m_angle = 0;
}

void CircularSpikedBall::place(const sf::Vector2f &position, float length)
{
    m_length = length;
    m_angular_velocity = m_length * 2.5;

    m_base.setPosition(position);
    m_chain.setPosition(position);

    sf::IntRect chain_texture_rectangle {
            0, 0,
            static_cast<int>(m_length),
            static_cast<int>(m_chain.getTexture()->getSize().y)
    };

    m_chain.setTextureRect(chain_texture_rectangle);
}

void CircularSpikedBall::update(double dt)
{
    sf::Vector2f base_position = m_base.getPosition();

    m_angle += m_angular_velocity * dt;

    if (m_angle > 360) m_angle -= 360;

    float x = m_length * std::cos(utils::to_radians(m_angle));
    float y = m_length * std::sin(utils::to_radians(m_angle));

    m_chain.setRotation(m_angle);
    m_spiked_ball.set_position(base_position.x + x, base_position.y + y);
}
