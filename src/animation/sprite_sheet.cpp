//
// Created by Gianni on 18/01/2024.
//

#include "sprite_sheet.hpp"

/* -- Frame -- */
SpriteSheet::Frame::Frame(int left, int top, int width, int height, const std::string& tag)
    : m_spritesheet_sub_rect(left, top, width, height)
    , m_frame_tag(tag)
{
}

SpriteSheet::Frame::Frame(const sf::IntRect& spritesheet_rect, const std::string& tag)
    : m_spritesheet_sub_rect(spritesheet_rect)
    , m_frame_tag(tag)
{
}

void SpriteSheet::Frame::set_spritesheet_rect(const sf::IntRect& rect)
{
    m_spritesheet_sub_rect = rect;
}

void SpriteSheet::Frame::set_frame_tag(const std::string& tag)
{
    m_frame_tag = tag;
}

const sf::IntRect& SpriteSheet::Frame::get_spritesheet_rect() const
{
    return m_spritesheet_sub_rect;
}

const std::string& SpriteSheet::Frame::get_frame_tag() const
{
    return m_frame_tag;
}


/* -- Animation -- */
SpriteSheet::SpriteSheet()
    : m_frames()
    , m_time_pre_frame(sf::Time::Zero)
    , m_looped(true)
{
}

SpriteSheet::SpriteSheet(int sprite_width, int sprite_height, uint32_t frame_count, sf::Time time_per_frame, bool looped)
    : m_looped(looped)
    , m_time_pre_frame(time_per_frame)
{
    m_frames.reserve(frame_count);

    for (int i = 0; i < frame_count; ++i)
        m_frames.emplace_back(i * sprite_width, 0, sprite_width, sprite_height);
}

void SpriteSheet::add_frame(const SpriteSheet::Frame &frame)
{
    m_frames.push_back(frame);
}

void SpriteSheet::add_frame(const sf::IntRect &spritesheet_rect, const std::string &tag)
{
    m_frames.emplace_back(spritesheet_rect, tag);
}

void SpriteSheet::set_time_pre_frame(sf::Time time_per_frame)
{
    m_time_pre_frame = time_per_frame;
}

void SpriteSheet::set_looped(bool looped)
{
    m_looped = looped;
}

void SpriteSheet::set_spritesheet_rect(size_t index, const sf::IntRect &rect)
{
    m_frames.at(index).set_spritesheet_rect(rect);
}

void SpriteSheet::set_frame_tag(size_t index, const std::string &tag)
{
    m_frames.at(index).set_frame_tag(tag);
}

void SpriteSheet::clear_frames()
{
    m_frames.clear();
}

const SpriteSheet::Frame& SpriteSheet::get_frame(size_t index) const
{
    return m_frames.at(index);
}

const sf::IntRect& SpriteSheet::get_frame_rect(size_t index) const
{
    return m_frames.at(index).get_spritesheet_rect();
}

const std::string& SpriteSheet::get_frame_tag(size_t index) const
{
    return m_frames.at(index).get_frame_tag();
}

size_t SpriteSheet::get_frame_count() const
{
    return m_frames.size();
}

bool SpriteSheet::is_looped() const
{
    return m_looped;
}

sf::Time SpriteSheet::get_time_pre_frame() const
{
    return m_time_pre_frame;
}
