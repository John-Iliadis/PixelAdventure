//
// Created by Gianni on 18/01/2024.
//

#include "animation.hpp"

/* -- Frame -- */
Animation::Frame::Frame(int left, int top, int width, int height, const std::string& tag)
    : m_spritesheet_sub_rect(left, top, width, height)
    , m_frame_tag(tag)
{
}

Animation::Frame::Frame(const sf::IntRect& spritesheet_rect, const std::string& tag)
    : m_spritesheet_sub_rect(spritesheet_rect)
    , m_frame_tag(tag)
{
}

void Animation::Frame::set_spritesheet_rect(const sf::IntRect& rect)
{
    m_spritesheet_sub_rect = rect;
}

void Animation::Frame::set_frame_tag(const std::string& tag)
{
    m_frame_tag = tag;
}

const sf::IntRect& Animation::Frame::get_spritesheet_rect() const
{
    return m_spritesheet_sub_rect;
}

const std::string& Animation::Frame::get_frame_tag() const
{
    return m_frame_tag;
}


/* -- Animation -- */
Animation::Animation()
    : m_frames()
    , m_time_pre_frame(sf::Time::Zero)
    , m_looped(true)
{
}

Animation::Animation(int sprite_width, int sprite_height, uint32_t frame_count, sf::Time time_per_frame, bool looped)
    : m_looped(looped)
    , m_time_pre_frame(time_per_frame)
{
    m_frames.reserve(frame_count);

    for (int i = 0; i < frame_count; ++i)
        m_frames.emplace_back(i * sprite_width, 0, sprite_width, sprite_height);
}

void Animation::add_frame(const Animation::Frame &frame)
{
    m_frames.push_back(frame);
}

void Animation::add_frame(const sf::IntRect &spritesheet_rect, const std::string &tag)
{
    m_frames.emplace_back(spritesheet_rect, tag);
}

void Animation::set_time_pre_frame(sf::Time time_per_frame)
{
    m_time_pre_frame = time_per_frame;
}

void Animation::set_looped(bool looped)
{
    m_looped = looped;
}

void Animation::set_spritesheet_rect(size_t index, const sf::IntRect &rect)
{
    m_frames.at(index).set_spritesheet_rect(rect);
}

void Animation::set_frame_tag(size_t index, const std::string &tag)
{
    m_frames.at(index).set_frame_tag(tag);
}

void Animation::clear_frames()
{
    m_frames.clear();
}

const Animation::Frame& Animation::get_frame(size_t index) const
{
    return m_frames.at(index);
}

const sf::IntRect& Animation::get_frame_rect(size_t index) const
{
    return m_frames.at(index).get_spritesheet_rect();
}

const std::string& Animation::get_frame_tag(size_t index) const
{
    return m_frames.at(index).get_frame_tag();
}

size_t Animation::get_frame_count() const
{
    return m_frames.size();
}

bool Animation::is_looped() const
{
    return m_looped;
}

sf::Time Animation::get_time_pre_frame() const
{
    return m_time_pre_frame;
}
