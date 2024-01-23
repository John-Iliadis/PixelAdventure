//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"


Player::Player()
{
    m_textures.load_directory_list("../data/player/player_textures.json");
    m_animations.load_from_file("../data/player/animations.json");

    current_state = new IdleState(*this);

    m_sprite_collider.set_hitbox_size(18, 26); // todo: load json
    m_sprite_collider.setPosition(200, 150);
    m_sprite_collider.setScale(2, 2); // todo: load json
    m_sprite_collider.set_origin_mid_bottom();
}

Player::~Player()
{
    delete current_state;
}

void Player::update(double dt)
{
    handle_real_time_input();
    x_axis_collision_callback(dt);

    PlayerState* new_state = current_state->update(*this, dt);

    change_state(new_state);

    apply_gravity();
    y_axis_collision_callback(dt);

    m_animations.update(dt);
    set_animation_frame();
}

void Player::handle_event(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
         m_data.time_since_last_jump_button_pressed.restart();

    PlayerState* new_state = current_state->handle_event(*this, event);

    change_state(new_state);
}

void Player::set_collision_callbacks(std::function<void(double)> x, std::function<void(double)> y)
{
    x_axis_collision_callback = std::move(x);
    y_axis_collision_callback = std::move(y);
}

void Player::set_animation(const std::string &id)
{
    m_animations.set_animation(id);
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
    m_sprite_collider.set_texture(m_textures.get(id));
}

void Player::set_position(float x, float y)
{
    m_sprite_collider.setPosition(x, y);
}

void Player::move(float x, float y)
{
    m_sprite_collider.move(x, y);
}

void Player::set_gravity(bool on)
{
    m_data.gravity = on ? m_data.gravity_speed : 0;
}

sf::FloatRect Player::get_hitbox() const
{
    return m_sprite_collider.get_hitbox();
}

sf::Vector2f Player::get_center() const
{
    return m_sprite_collider.get_sprite_center();
}

sf::Vector2f Player::get_position() const
{
    return m_sprite_collider.getPosition();
}

PlatformerData &Player::get_platformer_data()
{
    return m_data;
}

SpriteOrientation Player::get_orientation() const
{
    return m_sprite_collider.get_orientation();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite_collider);
}

void Player::handle_real_time_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    {
        m_data.velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_data.velocity.x = -m_data.move_speed;
        m_sprite_collider.set_orientation(SpriteOrientation::FACES_LEFT);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_data.velocity.x = m_data.move_speed;
        m_sprite_collider.set_orientation(SpriteOrientation::FACES_RIGHT);
    }
}

void Player::apply_gravity()
{
    m_data.velocity.y += m_data.gravity;
}

void Player::change_state(PlayerState *new_state)
{
    if (new_state)
    {
        delete current_state;
        current_state = new_state;
    }
}

void Player::set_animation_frame()
{
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
}
