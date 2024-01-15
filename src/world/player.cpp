//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"

static const sf::Vector2f player_speed {400, 400};

Player::Player(const TextureManager &texture_manager)
{
    m_sprite.setTexture(texture_manager.get("idle"));
    m_sprite.setTextureRect({0, 0, 32, 32});
    m_sprite.setScale(2, 2);
    m_sprite.setPosition(200, 200);

    m_hit_box = m_sprite.getGlobalBounds();
}

void Player::update(double dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_velocity.x = -player_speed.x * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_velocity.x = player_speed.x * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_velocity.y = -player_speed.y * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_velocity.y = player_speed.y * dt;

    m_sprite.move(m_velocity);
    m_hit_box = m_sprite.getGlobalBounds(); // todo: remove
}

void Player::handle_event(const sf::Event &event)
{
    if (event.type == sf::Event::KeyReleased)
        m_velocity = {0, 0};
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

const sf::FloatRect& Player::get_hit_box() const
{
    return m_hit_box;
}

void Player::move(float x, float y)
{
    m_sprite.move(x, y);
    m_hit_box = m_sprite.getGlobalBounds();
}

sf::Vector2f Player::get_center() const
{
    auto sprite_bounds = m_sprite.getGlobalBounds();

    return {sprite_bounds.left + sprite_bounds.width / 2.f,
            sprite_bounds.top + sprite_bounds.height / 2.f};
}
