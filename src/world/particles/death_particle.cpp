//
// Created by Gianni on 30/01/2024.
//

#include "death_particle.hpp"


const float DeathParticle::gravity = 9.8;
const float DeathParticle::speed_deceleration = 200;
const float DeathParticle::rotation_deceleration = 300;
const float DeathParticle::rotation_speed = 300;
const sf::Time DeathParticle::total_lifetime = sf::seconds(3);

DeathParticle::DeathParticle(Animation animation, const sf::Texture &texture, const sf::Vector2f &pos,
                             const sf::Vector2f &velocity, Orientation orientation)
    : m_animation(std::move(animation))
    , m_finished(false)
    , m_life_time(total_lifetime)
{
    set_velocity(velocity);

    m_sprite.setTexture(texture);
    m_sprite.setPosition(pos.x, pos.y - m_sprite.getGlobalBounds().height / 2.f);
    m_sprite.setTextureRect(m_animation.get_current_frame_rect());
    utils::set_origin_center(m_sprite);

    if (orientation == Orientation::FACES_LEFT)
        m_sprite.setScale(-1, 1);

    m_rotation = velocity.x > 0? rotation_speed : -rotation_speed;
}

void DeathParticle::update(double dt)
{
    apply_gravity();
    apply_deceleration(m_velocity.x, speed_deceleration, dt);
    apply_deceleration(m_rotation, rotation_deceleration, dt);
    update_sprite(dt);
    update_animation(dt);
    update_life_tile(dt);
}

bool DeathParticle::finished() const
{
    return m_finished;
}

void DeathParticle::apply_gravity()
{
    m_velocity.y += gravity;
}

void DeathParticle::apply_deceleration(float& value, float deceleration, double dt)
{
    if (std::abs(value) > 0)
    {
        float frame_deceleration = deceleration * dt;

        value += value > 0? -frame_deceleration : frame_deceleration;

        if (std::abs(value) < frame_deceleration)
            value = 0;
    }
}

void DeathParticle::update_sprite(double dt)
{
    m_sprite.move(m_velocity.x * dt, m_velocity.y * dt);
    m_sprite.rotate(m_rotation * dt);
}

void DeathParticle::update_animation(double dt)
{
    m_animation.update(dt);
    m_sprite.setTextureRect(m_animation.get_current_frame_rect());
}

void DeathParticle::update_life_tile(double dt)
{
    m_life_time -= sf::seconds(dt);

    if (m_life_time <= sf::Time::Zero)
        m_finished = true;
}

void DeathParticle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
