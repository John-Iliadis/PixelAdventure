//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_DEATH_PARTICLE_HPP
#define PLATFORMER_DEATH_PARTICLE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../../animation/animation.hpp"
#include "../../utilities/utils.hpp"
#include "../movable_object.hpp"
#include "../../enums/orientation.hpp"


class DeathParticle : public MovableObject, public sf::Drawable
{
public:
    DeathParticle(Animation animation, const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& velocity, Orientation orientation);
    void update(double dt);

    bool finished() const;

private:
    void apply_gravity();
    void apply_deceleration(float& value, float deceleration, double dt);
    void update_sprite(double dt);
    void update_animation(double dt);
    void update_life_time(double dt);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Animation m_animation;
    sf::Sprite m_sprite;
    sf::Time m_life_time;
    bool m_finished;
    float m_rotation;

    static const float gravity;
    static const float speed_deceleration;
    static const float rotation_deceleration;
    static const float rotation_speed;
    static const sf::Time total_lifetime;
};


#endif //PLATFORMER_DEATH_PARTICLE_HPP
