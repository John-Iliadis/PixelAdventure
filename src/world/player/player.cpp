//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"


Player::Player()
{
    m_textures.load_directory_list("../data/player/player_textures.json");
    m_platformer_data.load_platformer_data("../data/player/platformer_data.json");

    current_state = new IdleState(*this);

    scale(2, 2);
    setPosition(100, 100);
}

Player::~Player()
{
    delete current_state;
}

void Player::handle_event(const sf::Event &event)
{
    PlayerState* new_state = current_state->handle_event(*this, event);

    change_state(new_state);
}

void Player::update(double dt)
{
    handle_real_time_input();

    PlayerState* new_state = current_state->update(*this, dt);

    change_state(new_state);

    apply_gravity();
}

void Player::set_texture(const std::string &texture_id)
{
    m_sprite.setTexture(m_textures.get(texture_id), true);
}

void Player::set_texture_rect(const sf::IntRect &rect)
{
    m_sprite.setTextureRect(rect);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

sf::FloatRect Player::get_rectangle() const
{
    return getTransform().transformRect(m_sprite.getGlobalBounds());
}

sf::Vector2f Player::get_center() const
{
    auto rect = get_rectangle();

    return {rect.left + rect.width / 2.f,
            rect.top + rect.height / 2.f};
}

PlatformerData &Player::get_platformer_data()
{
    return m_platformer_data;
}

sf::Sprite &Player::get_sprite()
{
    return m_sprite;
}

bool Player::facing_right()
{
    return m_platformer_data.facing_right;
}

void Player::handle_real_time_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    {
        m_platformer_data.velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // todo : if not collided left
    {
        m_platformer_data.velocity.x = -m_platformer_data.move_speed;
        m_platformer_data.facing_right = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_platformer_data.velocity.x = m_platformer_data.move_speed;
        m_platformer_data.facing_right = true;
    }
}

void Player::apply_gravity()
{
    m_platformer_data.velocity.y += m_platformer_data.gravity;
}

void Player::change_state(PlayerState *new_state)
{
    if (new_state)
    {
        delete current_state;
        current_state = new_state;
    }
}
