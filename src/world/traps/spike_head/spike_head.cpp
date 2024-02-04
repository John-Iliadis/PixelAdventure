//
// Created by Gianni on 2/02/2024.
//

#include "spike_head.hpp"


static const std::string animations_filename = "../data/traps/spike_head/animations.json";
static const sf::Vector2f collider_size {26, 24};

SpikeHead::SpikeHead(const TextureManager &textures)
    : m_current_state(State::MOVING)
    , m_start_pos_index()
    , m_target_pos_index()
    , m_ellapsed()
    , m_duration()
{
    m_animations.load_from_file(animations_filename);
    m_animations.set_animation("spike_head_idle");

    m_textures["spike_head_idle"] = &textures.get("spike_head_idle");
    m_textures["spike_head_bottom_hit"] = &textures.get("spike_head_bottom_hit");
    m_textures["spike_head_left_hit"] = &textures.get("spike_head_left_hit");
    m_textures["spike_head_right_hit"] = &textures.get("spike_head_right_hit");
    m_textures["spike_head_top_hit"] = &textures.get("spike_head_top_hit");

    m_sprite_collider.set_texture(*m_textures.at("spike_head_idle"));
    m_sprite_collider.set_collider_size(collider_size);
    m_sprite_collider.set_origin(Origin::CENTER);
}

void SpikeHead::update(double dt)
{
    switch (m_current_state)
    {
        case State::MOVING:
        {
            update_moving_state(dt);
            break;
        }

        case State::STOPPING:
        {
            update_stopping_state(dt);
            break;
        }
    }

    update_animation(dt);
}

void SpikeHead::update_moving_state(double dt)
{
    m_ellapsed += dt;

    double t = m_ellapsed / m_duration;

    assert(!std::isinf(t));

    if (t > 1) t = 1;

    double easing = t == 0? 0 : std::pow(2, 10 * t - 10);

    sf::Vector2f start_pos = m_path.at(m_start_pos_index);
    sf::Vector2f target_pos = m_path.at(m_target_pos_index);

    sf::Vector2f new_pos = start_pos + (target_pos - start_pos) * static_cast<float>(easing);

    m_sprite_collider.set_position(new_pos);

    if (new_pos == target_pos)
    {
        m_ellapsed = 0;

        m_start_pos_index = (m_start_pos_index + 1) % m_path.size();
        m_target_pos_index = (m_target_pos_index + 1) % m_path.size();

        calculate_duration();

        sf::Vector2f vector = target_pos - start_pos;

        assert(vector != sf::Vector2f(0, 0));

        std::string next_animation;

        if (vector.x > 0)
            next_animation = "spike_head_right_hit";
        else if (vector.x < 0)
            next_animation = "spike_head_left_hit";
        else if (vector.y > 0)
            next_animation = "spike_head_bottom_hit";
        else if (vector.y < 0)
            next_animation = "spike_head_top_hit";

        on_moving_exit(next_animation);
    }
}

void SpikeHead::update_stopping_state(double dt)
{
    if (m_animations.finished())
    {
        on_stopping_exit();
    }
}

void SpikeHead::update_animation(double dt)
{
    m_animations.update(dt);
    m_sprite_collider.set_texture_rect(m_animations.get_current_frame_rect());
}


void SpikeHead::set_path(std::vector<sf::Vector2f>&& path)
{
    m_path = std::move(path);
}

void SpikeHead::set_spawn_pos_index(uint8_t index)
{
    assert(!m_path.empty());

    m_start_pos_index = index;
    m_target_pos_index = (index + 1) % m_path.size();

    m_sprite_collider.set_position(m_path.at(m_start_pos_index));

    calculate_duration();
}

void SpikeHead::calculate_duration()
{
    // todo: tune this
    m_duration = utils::get_distance(m_path.at(m_start_pos_index), m_path.at(m_target_pos_index)) / 128;
    m_duration = std::clamp(m_duration, 0.4, 1.5);
}

void SpikeHead::on_moving_exit(const std::string &animation_name)
{
    m_current_state = State::STOPPING;

    m_animations.set_animation(animation_name);
    m_sprite_collider.set_texture(*m_textures[animation_name]);
}

void SpikeHead::on_stopping_exit()
{
    m_current_state = State::MOVING;

    m_animations.set_animation("spike_head_idle");
    m_sprite_collider.set_texture(*m_textures["spike_head_idle"]);
}

sf::FloatRect SpikeHead::get_collider() const
{
    return m_sprite_collider.get_collider();
}

void SpikeHead::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite_collider);
}
