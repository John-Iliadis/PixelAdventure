//
// Created by Gianni on 18/01/2024.
//

#include "looping_animation.hpp"


LoopingAnimation::LoopingAnimation(uint32_t texture_width, uint32_t texture_height, uint32_t frame_count, sf::Time time_per_frame, bool playing)
    : Animation(texture_width, texture_height, frame_count, time_per_frame, playing)
{
}

void LoopingAnimation::update()
{
    if (!m_playing) return;

    if (m_clock.getElapsedTime() >= m_time_pre_frame)
    {
        m_frame_index++;

        if (m_frame_index == m_frame_count)
            m_frame_index = 0;

        m_clock.restart();
    }
}