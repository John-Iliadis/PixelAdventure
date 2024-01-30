//
// Created by Gianni on 30/01/2024.
//

#include "checkpoint.hpp"


static const std::string animation_dir = "../data/checkpoints/animations.json";

Checkpoint::Checkpoint(const TextureManager &texture_manager)
{
    m_animations.load_from_file(animation_dir);

    m_textures.emplace(std::make_pair("checkpoint_idle", &texture_manager.get("checkpoint_idle")));
    m_textures.emplace(std::make_pair("checkpoint_triggered", &texture_manager.get("checkpoint_triggered")));
    m_textures.emplace(std::make_pair("checkpoint_flag_out", &texture_manager.get("checkpoint_flag_out")));

    m_current_state = State::IDLE;
    on_idle_enter();

    m_sprite.set_collider_size(m_sprite.get_sprite_rect().getSize());
    m_sprite.set_origin(Origin::CENTER_BOTTOM);
}

void Checkpoint::activate()
{
    m_current_state = State::TRIGGERED;
    on_triggered_enter();
}

void Checkpoint::deactivate()
{
    m_current_state = State::IDLE;
    on_idle_enter();
}

void Checkpoint::set_position(float x, float y)
{
    m_sprite.set_position(x, y);
}

void Checkpoint::set_position(const sf::Vector2f &pos)
{
    m_sprite.set_position(pos);
}

void Checkpoint::update(double dt)
{
    switch (m_current_state)
    {
        case State::TRIGGERED:
        {
            if (m_animations.finished())
            {
                m_current_state = State::FLAG_OUT;
                on_flag_out_enter();
            }

            break;
        }
    }

    m_animations.update(dt);
    m_sprite.set_texture_rect(m_animations.get_current_frame_rect());
}

sf::FloatRect Checkpoint::get_collider() const
{
    return m_sprite.get_collider();
}

sf::Vector2f Checkpoint::get_position() const
{
    return m_sprite.get_position();
}

void Checkpoint::set_animation(const std::string &id)
{
    m_animations.set_animation(id);
    m_sprite.set_texture(*m_textures[id]);
}

void Checkpoint::on_idle_enter()
{
    set_animation("checkpoint_idle");
}

void Checkpoint::on_triggered_enter()
{
    set_animation("checkpoint_triggered");
}

void Checkpoint::on_flag_out_enter()
{
    set_animation("checkpoint_flag_out");
}

void Checkpoint::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

bool Checkpoint::is_active() const
{
    return m_current_state != State::IDLE;
}
