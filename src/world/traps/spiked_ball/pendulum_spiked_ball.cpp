//
// Created by Gianni on 3/02/2024.
//

#include "pendulum_spiked_ball.hpp"


const float PendulumSpikedBall::m_gravity = 1.f;
const float PendulumSpikedBall::m_initial_angle = 86;

PendulumSpikedBall::PendulumSpikedBall(TextureManager &textures)
    : SpikedBall(textures)
{
    m_angle = m_initial_angle;
}

void PendulumSpikedBall::place(const sf::Vector2f& position, float length)
{
    m_length = length;

    m_base.setPosition(position);
    m_chain.setPosition(position);

    sf::IntRect chain_texture_rectangle {
        0, 0,
        static_cast<int>(m_length),
        static_cast<int>(m_chain.getTexture()->getSize().y)
    };

    m_chain.setTextureRect(chain_texture_rectangle);
}

void PendulumSpikedBall::update(double dt)
{
    sf::Vector2f base_position = m_base.getPosition();

    float angular_acceleration = -m_gravity * std::sin(utils::to_radians(m_angle)) / m_length;
    m_angular_velocity += angular_acceleration;
    m_angle += m_angular_velocity;

    float x = m_length * std::sin(m_angle * M_PI / 180);
    float y = m_length * std::cos(m_angle * M_PI / 180);

    float angle = utils::to_degrees(std::atan(y / x));

    if (angle < 0) angle = 180 + angle;

    m_chain.setRotation(std::abs(angle));
    m_spiked_ball.set_position(base_position.x + x, base_position.y + y);
}
