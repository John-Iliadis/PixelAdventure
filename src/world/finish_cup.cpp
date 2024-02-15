//
// Created by Gianni on 15/02/2024.
//

#include "finish_cup.hpp"


static const std::string animations_path = "../data/finish_cup/animations.json";

FinishCup::FinishCup(const TextureManager &textures, const sf::Vector2f &position)
    : m_current_state(FinishCup::State::IDLE)
{
    m_animations.load_from_file(animations_path);
    m_animations.set_animation("finish_idle");

    m_textures["finish_idle"] = &textures.get("finish_idle");
    m_textures["finish_triggered"] = &textures.get("finish_triggered");

    m_sprite.setTexture(*m_textures.at("finish_idle"));
    m_sprite.setPosition(position);
    m_sprite.setTextureRect(m_animations.get_current_frame_rect());
    utils::set_origin(m_sprite, Origin::CENTER_BOTTOM);
}

void FinishCup::update(Player &player, double dt)
{
    switch (m_current_state)
    {
        case FinishCup::State::IDLE:
        {
            if (player.get_collider().intersects(m_sprite.getGlobalBounds()))
            {
                player.set_accepting_input(false);
                player.set_velocity(0, player.get_velocity().y);
                m_current_state = FinishCup::State::TRIGGERED;
                m_animations.set_animation("finish_triggered");
                m_sprite.setTexture(*m_textures.at("finish_triggered"));
                SoundPlayer::play_sound("finish");
                MusicPlayer::stop();
            }

            break;
        }

        case FinishCup::State::TRIGGERED:
        {
            break;
        }

        default:
            assert(false);
    }

    m_animations.update(dt);
    m_sprite.setTextureRect(m_animations.get_current_frame_rect());
}

void FinishCup::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

bool FinishCup::triggered() const
{
    return m_current_state == FinishCup::State::TRIGGERED;
}
