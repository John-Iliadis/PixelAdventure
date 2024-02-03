//
// Created by Gianni on 3/02/2024.
//

#ifndef PLATFORMER_SPIKED_BALL_HPP
#define PLATFORMER_SPIKED_BALL_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "../../../asset_managers/texture_manager.hpp"
#include "../../../utilities/utils.hpp"
#include "../../sprite_collider.hpp"
#include "../trap.hpp"


class SpikedBall : public Trap
{
public:
    SpikedBall(TextureManager& textures);
    virtual ~SpikedBall() = default;

    virtual void place(const sf::Vector2f& position, float length) = 0;

    sf::FloatRect get_collider() const override;

protected:
    SpriteCollider m_spiked_ball;
    sf::Sprite m_chain;
    sf::Sprite m_base;

    float m_angle;
    float m_length;
    float m_angular_velocity;

private: // todo: maybe make this protected
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //PLATFORMER_SPIKED_BALL_HPP
