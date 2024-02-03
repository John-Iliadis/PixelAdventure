//
// Created by Gianni on 3/02/2024.
//

#ifndef PLATFORMER_CIRCULAR_SPIKED_BALL_HPP
#define PLATFORMER_CIRCULAR_SPIKED_BALL_HPP

#include "spiked_ball.hpp"


class CircularSpikedBall : public SpikedBall
{
public:
    CircularSpikedBall(TextureManager& texture_manager);

    void place(const sf::Vector2f &position, float length) override;

    void update(double dt) override;
};


#endif //PLATFORMER_CIRCULAR_SPIKED_BALL_HPP
