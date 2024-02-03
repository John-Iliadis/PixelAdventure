//
// Created by Gianni on 3/02/2024.
//

#ifndef PLATFORMER_PENDULUM_SPIKED_BALL_HPP
#define PLATFORMER_PENDULUM_SPIKED_BALL_HPP

#include "spiked_ball.hpp"


class PendulumSpikedBall : public SpikedBall
{
public:
    PendulumSpikedBall(TextureManager& textures);

    void place(const sf::Vector2f& position, float length) override;

    void update(double dt) override;

private:
    static const float m_gravity;
    static const float m_initial_angle;
};


#endif //PLATFORMER_PENDULUM_SPIKED_BALL_HPP
