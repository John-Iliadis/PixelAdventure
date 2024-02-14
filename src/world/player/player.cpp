//
// Created by Gianni on 13/01/2024.
//

#include "player.hpp"


static std::string animation_filepath = "../data/player/animations.json";
static std::string platformer_data_path = "../data/player/platformer_data.json";

Player::Player(GameContext& context)
{
    setup_textures(*context.texture_manager);

    m_animations.load_from_file(animation_filepath);
    m_data.load_from_file(platformer_data_path);

    m_orientation = Orientation::FACES_RIGHT;
    m_current_state = new IdleState(*this);

    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
    m_sprite_collider.set_collider_size(m_data.collider_size);
    m_sprite_collider.set_origin(Origin::CENTER_BOTTOM);
}

Player::~Player()
{
    delete m_current_state;
}

void Player::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        m_data.jump_pressed_ellapsed_time = m_data.jump_pressed_remember_time;
}

void Player::update(double dt)
{
    handle_input();
    update_physics(dt);
    handle_state();
    update_animation(dt);

    m_data.jump_pressed_ellapsed_time -= dt;
    m_move_camera_callback();
}

void Player::handle_input()
{
    if (!m_data.alive) return;

    using namespace sf;
    bool (*key_pressed)(Keyboard::Key) = Keyboard::isKeyPressed;

    if (key_pressed(Keyboard::Left) && key_pressed(Keyboard::Right)
        || (!key_pressed(Keyboard::Left) && !key_pressed(Keyboard::Right)))
    {
        m_data.velocity.x = 0;
    }
    else if (key_pressed(Keyboard::Right))
    {
        m_data.velocity.x = m_data.move_speed;
        set_orientation(Orientation::FACES_RIGHT);
    }
    else if (key_pressed(Keyboard::Left))
    {
        m_data.velocity.x = -m_data.move_speed;
        set_orientation(Orientation::FACES_LEFT);
    }
}

void Player::update_physics(double dt)
{
    apply_gravity();
    m_resolve_collision_callback(dt);
}

void Player::handle_state()
{
    PlayerState* new_state = m_current_state->update(*this);
    change_state(new_state);
}

void Player::update_animation(double dt)
{
    m_animations.update(dt);
    set_animation_frame();
}

void Player::set_collision_callback(std::function<void(double)> callback)
{
    m_resolve_collision_callback = std::move(callback);
}

void Player::set_animation(const std::string &id)
{
    m_animations.set_animation(id);
    m_sprite_collider.set_texture(*m_textures[id]);
}

void Player::set_position(float x, float y)
{
    m_sprite_collider.set_position(x, y);
}

void Player::move(float x, float y)
{
    m_sprite_collider.move(x, y);
}

void Player::set_gravity(bool on)
{
    m_data.gravity = on ? m_data.gravity_speed : 0;
}

sf::FloatRect Player::get_collider() const
{
    return m_sprite_collider.get_collider();
}

sf::Vector2f Player::get_center() const
{
    auto rect = m_sprite_collider.get_sprite_rect();

    return {rect.left + rect.width / 2.f,
            rect.top + rect.height / 2.f};
}

sf::Vector2f Player::get_position() const
{
    return m_sprite_collider.get_position();
}

Orientation Player::get_orientation() const
{
    return m_orientation;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite_collider);
}

void Player::apply_gravity()
{
    m_data.velocity.y += m_data.gravity;
}

void Player::change_state(PlayerState *new_state)
{
    if (new_state)
    {
        delete m_current_state;
        m_current_state = new_state;
    }
}

void Player::set_animation_frame()
{
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
}

sf::Vector2f Player::get_velocity() const
{
    return m_data.velocity;
}

float Player::get_wall_sliding_speed() const
{
    return m_data.wall_sliding_speed;
}

bool Player::previously_jumped() const
{
    return m_data.previously_jumped;
}

bool Player::previously_double_jumped() const
{
    return m_data.previously_double_jumped;
}

bool Player::touching_wall() const
{
    return m_data.touching_wall;
}

void Player::set_previously_jumped(bool prev_jumped)
{
    m_data.previously_jumped = prev_jumped;
}

void Player::set_previously_double_jumped(bool prev_double_jumped)
{
    m_data.previously_double_jumped = prev_double_jumped;
}

void Player::jump()
{
    m_data.jump_pressed_ellapsed_time = 0;
    m_data.velocity.y = m_data.jump_speed;
}

void Player::set_velocity(float x, float y)
{
    m_data.velocity = {x, y};
}

void Player::set_touching_wall(bool touching_wall)
{
    m_data.touching_wall = touching_wall;
}

float Player::get_jump_pressed_ellapsed_time() const
{
    return m_data.jump_pressed_ellapsed_time;
}

void Player::set_position(const sf::Vector2f &pos)
{
    set_position(pos.x, pos.y);
}

void Player::set_orientation(Orientation orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    m_sprite_collider.scale(-1, 1);
}

void Player::setup_textures(const TextureManager &textures)
{
    m_textures["idle"] = &textures.get("idle");
    m_textures["falling"] = &textures.get("falling");
    m_textures["running"] = &textures.get("running");
    m_textures["jumping"] = &textures.get("jumping");
    m_textures["wall_sliding"] = &textures.get("wall_sliding");
    m_textures["double_jumping"] = &textures.get("double_jumping");
    m_textures["respawning"] = &textures.get("respawning");
}

void Player::set_respawn_position(const sf::Vector2f &respawn_pos)
{
    m_data.respawn_position = respawn_pos;
}

void Player::respawn()
{
    delete m_current_state;
    m_current_state = new RespawningState(*this);

    m_sprite_collider.set_collider_size(m_data.collider_size);
    m_sprite_collider.set_color({255, 255, 255, 255});
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
}

void Player::die()
{
    m_data.alive = false;
    m_sprite_collider.set_color(sf::Color::Transparent);
    m_sprite_collider.set_collider_size(0, 0);
    SoundPlayer::play_sound("death");
    m_spawn_death_particle_callback();
    m_camera_transition_callback();
}

void Player::set_death_particle_callback(std::function<void()> callback)
{
    m_spawn_death_particle_callback = std::move(callback);
}

bool Player::is_alive() const
{
    return m_data.alive;
}

void Player::set_camera_transition_callback(std::function<void()> callback)
{
    m_camera_transition_callback = std::move(callback);
}

sf::Vector2f Player::get_respawn_pos() const
{
    return {m_data.respawn_position.x, m_data.respawn_position.y};
}

bool Player::animation_finished() const
{
    return m_animations.finished();
}

void Player::set_alive(bool alive)
{
    m_data.alive = alive;
}

void Player::set_origin(Origin origin)
{
    m_sprite_collider.set_origin(origin);
}

sf::FloatRect Player::get_sprite_size() const
{
    return m_sprite_collider.get_sprite_rect();
}

void Player::set_move_camera_callback(std::function<void()> callback)
{
    m_move_camera_callback = std::move(callback);
}
