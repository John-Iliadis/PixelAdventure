//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"


Player::Player()
{
    m_textures.load_directory_list("../data/player/player_textures.json");
    m_platformer_data.load_platformer_data("../data/player/platformer_data.json");

    current_state = new IdleState(*this);

    m_platformer_data.collision_rect.setPosition(200, 150);
    m_sprite.setScale(2, 2);
    m_sprite.setPosition(200, 150);
    set_origin_mid_bottom(m_sprite);
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
    x_axis_collision_callback(dt);

    PlayerState* new_state = current_state->update(*this, dt);

    change_state(new_state);

    apply_gravity();
    y_axis_collision_callback(dt);

    m_sprite.setPosition(m_platformer_data.collision_rect.getPosition());
}

void Player::set_texture(const std::string &texture_id)
{
    m_sprite.setTexture(m_textures.get(texture_id), true);
}

void Player::set_texture_rect(const sf::IntRect &rect)
{
    m_sprite.setTextureRect(rect);
}

void Player::set_position(float x, float y)
{
    m_platformer_data.collision_rect.setPosition(x, y);
}

void Player::move(float x, float y)
{
    m_platformer_data.collision_rect.move(x, y);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
    target.draw(m_platformer_data.collision_rect);
}

sf::FloatRect Player::get_rectangle() const
{
    return m_platformer_data.collision_rect.getGlobalBounds();
}

sf::Vector2f Player::get_center() const
{
    auto rect = m_sprite.getGlobalBounds();

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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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

void Player::set_collision_callbacks(std::function<void(double)> x, std::function<void(double)> y)
{
    x_axis_collision_callback = std::move(x);
    y_axis_collision_callback = std::move(y);
}

sf::Vector2f Player::get_position() const
{
    return m_platformer_data.collision_rect.getPosition();
}
