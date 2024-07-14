//
// Created by Gianni on 30/01/2024.
//

#include "animation.hpp"


Animation::Animation()
    : m_frame_index()
    , m_playing(false)
    , m_looped(false)
{
}

Animation::Animation(int sprite_width, int sprite_height, uint32_t frame_count, sf::Time time_per_frame, bool looped)
    : m_sprite_sheet(sprite_width, sprite_height, frame_count)
    , m_current_frame(m_sprite_sheet.get_frame(0))
    , m_frame_index()
    , m_time_per_frame(time_per_frame)
    , m_looped(looped)
    , m_playing(true)
{
}

Animation::Animation(SpriteSheet&& sprite_sheet, sf::Time time_per_frame, bool looped)
    : m_sprite_sheet(std::move(sprite_sheet))
    , m_current_frame(m_sprite_sheet.get_frame(0))
    , m_frame_index()
    , m_time_per_frame(time_per_frame)
    , m_looped(looped)
    , m_playing(true)
{
}

void Animation::play()
{
    m_playing = true;
    m_ellapsed = sf::Time::Zero;
}

void Animation::pause()
{
    m_playing = false;
}

void Animation::reset()
{
    m_frame_index = 0;
    m_current_frame = m_sprite_sheet.get_frame(m_frame_index);
    m_ellapsed = sf::Time::Zero;
}

void Animation::update(double dt)
{
    if (!m_playing) return;

    m_ellapsed += sf::seconds(dt);

    if (m_sprite_sheet.frame_count() <= 1) return;

    if (m_ellapsed >= m_time_per_frame)
    {
        m_ellapsed = sf::microseconds(m_ellapsed.asMicroseconds() % m_time_per_frame.asMicroseconds());

        if (m_frame_index + 1 < m_sprite_sheet.frame_count())
        {
            m_current_frame = m_sprite_sheet.get_frame(++m_frame_index);
        }
        else if (m_looped)
        {
            reset();
        }
        else
        {
            m_playing = false;
        }
    }
}

const SpriteSheet::Frame& Animation::get_current_frame() const
{
    return m_current_frame;
}

const sf::IntRect &Animation::get_current_frame_rect() const
{
    return m_current_frame.get_spritesheet_rect();
}

const std::string &Animation::get_current_frame_tag() const
{
    return m_current_frame.get_frame_tag();
}

bool Animation::finished() const
{
    if (m_looped)
    {
        return false;
    }
    else if (m_frame_index + 1 == m_sprite_sheet.frame_count())
    {
        return true;
    }

    return false;
}

Animation::Animation(const Animation& other) noexcept
{
    m_sprite_sheet = other.m_sprite_sheet;
    m_current_frame = other.m_current_frame;
    m_frame_index = other.m_frame_index;
    m_ellapsed = other.m_ellapsed;
    m_time_per_frame = other.m_time_per_frame;
    m_playing = other.m_playing;
    m_looped = other.m_looped;
}

Animation &Animation::operator=(const Animation& other) noexcept
{
    if (this != &other)
    {
        m_sprite_sheet = other.m_sprite_sheet;
        m_current_frame = other.m_current_frame;
        m_frame_index = other.m_frame_index;
        m_ellapsed = other.m_ellapsed;
        m_time_per_frame = other.m_time_per_frame;
        m_playing = other.m_playing;
        m_looped = other.m_looped;
    }

    return *this;
}

bool Animation::playing() const
{
    return m_playing;
}
