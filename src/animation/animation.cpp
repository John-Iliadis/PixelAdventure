//
// Created by Gianni on 18/01/2024.
//

#include "animation.hpp"


Animation::Animation()
    : m_frame_count()
    , m_frame_index()
    , m_playing(false)
{
}

Animation::Animation(uint32_t texture_width, uint32_t texture_height, uint32_t frame_count, sf::Time time_per_frame, bool playing)
    : m_time_pre_frame(time_per_frame)
    , m_frame_count(frame_count)
    , m_frame_index()
    , m_playing(playing)
{
    for (int i = 0; i < frame_count; ++i)
    {
        m_frames.emplace_back(i * texture_width, 0, texture_width, texture_height);
        m_frames_reversed.emplace_back(i * texture_width + texture_width, 0, -texture_width, texture_height);
    }
}

void Animation::start()
{
    m_playing = true;
    m_clock.restart();
}

void Animation::stop()
{
    m_playing = false;
}

void Animation::reset()
{
    m_frame_index = 0;
}

const sf::Rect<uint32_t>& Animation::get_current_frame(bool facing_right) const
{
    if (facing_right)
        return m_frames.at(m_frame_index);
    else
        return m_frames_reversed.at(m_frame_index);
}
