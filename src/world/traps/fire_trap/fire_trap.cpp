//
// Created by Gianni on 1/02/2024.
//

#include "fire_trap.hpp"


static const std::string animation_filename = "../data/traps/fire_trap/animations.json";
static const sf::Vector2f collider_size = {16, 16};

FireTrap::FireTrap(const TextureManager &textures)
    : m_on_time()
    , m_off_time()
    , m_ellapsed()
    , m_current_state(State::FIRE_OFF)
{
    m_animations.load_from_file(animation_filename);
    m_animations.set_animation("fire_off");

    m_textures["fire_on"] = &textures.get("fire_on");
    m_textures["fire_off"] = &textures.get("fire_off");

    m_sprite_collider.set_texture(*m_textures["fire_off"]);
    m_sprite_collider.set_collider_size(collider_size);
    m_sprite_collider.set_origin(Origin::TOP_LEFT);
}

void FireTrap::place(const sf::Vector2f &pos, int rotation)
{
    assert(rotation % 90 == 0);

    m_sprite_collider.set_rotation(rotation);

    sf::Vector2f sprite_size = static_cast<sf::Vector2f>(m_textures["fire_off"]->getSize());

    switch (rotation)
    {
        case 0:
            m_sprite_collider.set_position(pos.x, pos.y - sprite_size.y / 2);
            break;
        case 90:
            m_sprite_collider.set_position(pos.x + sprite_size.y, pos.y);
            break;
        case 180:
            m_sprite_collider.set_position(pos.x + sprite_size.x, pos.y + sprite_size.y);
            break;
        case 270:
            m_sprite_collider.set_position(pos.x - sprite_size.y / 2, pos.y + sprite_size.x);
            break;
        default:
            assert(false);
    }
}

void FireTrap::set_timer(float on_time, float off_time)
{
    m_on_time = on_time;
    m_off_time = off_time;
}

sf::Rect<float> FireTrap::get_collider() const
{
    return m_sprite_collider.get_collider();
}

void FireTrap::update(double dt)
{
    assert(m_on_time != 0 && m_off_time != 0);

    m_ellapsed += dt;

    switch (m_current_state)
    {
        case State::FIRE_ON:
        {
            if (m_ellapsed >= m_on_time)
            {
                on_fire_on_exit();
                m_ellapsed = 0;
            }

            break;
        }

        case State::FIRE_OFF:
        {
            if (m_ellapsed >= m_off_time)
            {
                on_fire_off_exit();
                m_ellapsed = 0;
            }

            break;
        }
    }

    update_animation(dt);
}

void FireTrap::update_animation(double dt)
{
    m_animations.update(dt);
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
}

void FireTrap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite_collider);
}

void FireTrap::on_fire_on_exit()
{
    m_current_state = State::FIRE_OFF;
    m_animations.set_animation("fire_off");
    m_sprite_collider.set_texture(*m_textures["fire_off"]);
    m_sprite_collider.set_collider_size(0, 0);
}

void FireTrap::on_fire_off_exit()
{
    m_current_state = State::FIRE_ON;
    m_animations.set_animation("fire_on");
    m_sprite_collider.set_texture(*m_textures["fire_on"]);
    m_sprite_collider.set_collider_size(collider_size);
}
