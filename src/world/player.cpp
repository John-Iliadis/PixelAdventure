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

    setPosition(200, 200);
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
}

void Player::handle_event(const sf::Event &event)
{
    if (event.type == sf::Event::KeyReleased)
        m_velocity = {0, 0};
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform = getTransform();
    target.draw(m_sprite, states);
}

sf::FloatRect Player::get_rectangle() const
{
    return getTransform().transformRect(m_sprite.getGlobalBounds());
}

sf::Vector2f Player::get_center() const
{
    auto sprite_bounds = get_rectangle();

    return {sprite_bounds.left + sprite_bounds.width / 2.f,
            sprite_bounds.top + sprite_bounds.height / 2.f};
}

const sf::Vector2f &Player::get_velocity() const
{
    return m_velocity;
}
