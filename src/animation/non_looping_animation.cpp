//
// Created by Gianni on 18/01/2024.
//

#include "non_looping_animation.hpp"
#include <iostream>

NonLoopingAnimation::NonLoopingAnimation(uint32_t texture_width, uint32_t texture_height, uint32_t frame_count, sf::Time time_per_frame, bool playing)
    : Animation(texture_width, texture_height, frame_count, time_per_frame, playing)
    , m_ended(false)
    , m_first_play(true)
{
}

void NonLoopingAnimation::reset()
{
    Animation::reset();
    m_ended = false;
    m_first_play = true;
}

void NonLoopingAnimation::update(sf::Sprite &sprite)
{
    if (!m_playing || m_ended) return;

    if (m_clock.getElapsedTime() >= m_time_pre_frame)
    {
        if (m_first_play)
        {
            m_first_play = false;
            return;
        }

        set_next_frame();
        sprite.setTextureRect(static_cast<sf::IntRect>(m_frames.at(m_frame_index)));
        m_clock.restart();
    }
}

bool NonLoopingAnimation::ended() const
{
    return m_ended;
}

void NonLoopingAnimation::set_next_frame()
{
    m_frame_index++;

    if (m_frame_index == m_frame_count - 1)
        m_ended = true;
}
