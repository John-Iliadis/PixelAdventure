//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"


Player::Player()
{
    m_textures.load_directory_list("../data/player/player_textures.json");
    m_animations.load_from_file("../data/player/animations.json");
    init_platformer_data();

    current_state = new IdleState(*this);

    m_sprite_collider.set_hitbox_size(18, 26); // todo: load json
    m_sprite_collider.setPosition(200, 300);
    m_sprite_collider.set_origin_mid_bottom();
}

Player::~Player()
{
    delete current_state;
}

void Player::update(double dt)
{
    m_jump_pressed_ellapsed_time -= dt;

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
        m_jump_pressed_ellapsed_time = m_jump_pressed_remember_time;

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
    m_gravity = on ? m_gravity_speed : 0;
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
        m_velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_velocity.x = m_move_speed;
        m_sprite_collider.set_orientation(SpriteOrientation::FACES_RIGHT);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_velocity.x = -m_move_speed;
        m_sprite_collider.set_orientation(SpriteOrientation::FACES_LEFT);
    }
}

void Player::apply_gravity()
{
    m_velocity.y += m_gravity;
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

sf::Vector2f Player::get_velocity() const
{
    return m_velocity;
}

float Player::get_wall_sliding_speed() const
{
    return m_wall_sliding_speed;
}

bool Player::previously_jumped() const
{
    return m_previously_jumped;
}

bool Player::previously_double_jumped() const
{
    return m_previously_double_jumped;
}

bool Player::touching_wall() const
{
    return m_touching_wall;
}

void Player::init_platformer_data()
{
    std::ifstream file("../data/player/platformer_data.json");

    if (!file.is_open())
        throw std::runtime_error("Player::init_platformer_data - Failed to open file\n");

    nlohmann::json json = nlohmann::json::parse(file);

    m_velocity = {};
    m_move_speed = json["move_speed"].get<float>();
    m_gravity_speed = json["gravity_speed"].get<float>();
    m_gravity = m_gravity_speed;
    m_wall_sliding_speed = json["wall_sliding_speed"].get<float>();
    m_jump_speed = json["jump_speed"].get<float>();
    m_jump_pressed_remember_time = json["jump_pressed_remember_time"].get<float>();
    m_jump_pressed_ellapsed_time = 0;
    m_previously_jumped = false;
    m_previously_double_jumped = false;
    m_touching_wall = false;

    file.close();
}

void Player::set_previously_jumped(bool prev_jumped)
{
    m_previously_jumped = prev_jumped;
}

void Player::set_previously_double_jumped(bool prev_double_jumped)
{
    m_previously_double_jumped = prev_double_jumped;
}

void Player::jump()
{
    m_jump_pressed_ellapsed_time = 0;
    m_velocity.y = m_jump_speed;
}

void Player::set_velocity(float x, float y)
{
    m_velocity = {x, y};
}

void Player::set_touching_wall(bool touching_wall)
{
    m_touching_wall = touching_wall;
}

float Player::get_jump_pressed_ellapsed_time() const
{
    return m_jump_pressed_ellapsed_time;
}
