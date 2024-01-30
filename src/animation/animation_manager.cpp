//
// Created by Gianni on 22/01/2024.
//

#include "animation_manager.hpp"
#include <iostream>

AnimationManager::AnimationManager()
        : m_current_animation_id()
        , m_current_frame_index()
        , m_playing(true)
{
}

AnimationManager::AnimationManager(const std::string &file_name)
        : m_current_animation_id()
        , m_current_frame_index()
        , m_playing(true)
{
    load_from_file(file_name);
}

void AnimationManager::load_from_file(const std::string &file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
        throw std::runtime_error("AnimationManager<ID>::AnimationManager - Failed to open file " + file_name);

    if (!m_animations.empty())
    {
        m_animations.clear();
        m_current_animation_id = "";
        m_current_frame_index = 0;
        m_ellapsed = sf::Time::Zero;
        m_playing = true;
    }

    nlohmann::json json = nlohmann::json::parse(file);

    int width = json["sprite_width"].get<int>();
    int height = json["sprite_height"].get<int>();

    for (const auto& animation : json["animations"])
    {
        Animation l_anim {
            width,
            height,
            animation["frame_count"].get<uint32_t>(),
            sf::milliseconds(animation["frame_time_milliseconds"].get<int>()),
            animation["looped"].get<bool>()
        };

        std::string id = animation["id"].get<std::string>();

        if (animation.contains("tags"))
        {
            for (const auto& tag : animation["tags"])
            {
                size_t index = tag["index"].get<size_t>();
                std::string value = tag["value"].get<std::string>();

                l_anim.set_frame_tag(index, value);
            }
        }

        m_animations.emplace(std::make_pair(std::move(id), std::move(l_anim)));
    }

    file.close();
}

void AnimationManager::add_animation(std::pair<std::string, Animation>&& animation)
{
    m_animations.emplace(animation);
}

void AnimationManager::play()
{
    m_playing = true;
    m_ellapsed = sf::Time::Zero;
}

void AnimationManager::pause()
{
    m_playing = false;
}

void AnimationManager::reset()
{
    m_current_frame_index = 0;
    m_ellapsed = sf::Time::Zero;
}

void AnimationManager::set_animation(const std::string& id)
{
    assert(m_animations.find(id) != m_animations.end());

    m_current_animation_id = id;
    m_current_frame_index = 0;
    m_ellapsed = sf::Time::Zero;
    m_playing = true;
}

void AnimationManager::update(double dt)
{
    assert(!m_animations.empty() && !m_current_animation_id.empty());

    if (!m_playing) return;

    m_ellapsed += sf::seconds(dt);

    Animation& current_animation = m_animations[m_current_animation_id];

    if (current_animation.get_frame_count() <= 1) return;

    sf::Time time_per_frame = current_animation.get_time_pre_frame();

    if (m_ellapsed >= time_per_frame)
    {
        m_ellapsed = sf::microseconds(m_ellapsed.asMicroseconds() % time_per_frame.asMicroseconds());

        if (m_current_frame_index + 1 < current_animation.get_frame_count())
        {
            ++m_current_frame_index;
        }
        else if (!current_animation.is_looped())
        {
            m_playing = false;
        }
        else
        {
            m_current_frame_index = 0;
        }
    }
}

const Animation::Frame& AnimationManager::get_current_frame() const
{
    assert(!m_animations.empty());
    return m_animations.at(m_current_animation_id).get_frame(m_current_frame_index);
}

const sf::IntRect &AnimationManager::get_current_frame_rect() const
{
    assert(!m_animations.empty());
    return m_animations.at(m_current_animation_id).get_frame_rect(m_current_frame_index);
}

const std::string &AnimationManager::get_current_frame_tag() const
{
    assert(!m_animations.empty());
    return m_animations.at(m_current_animation_id).get_frame_tag(m_current_frame_index);
}

bool AnimationManager::animation_finished() const
{
    auto& current_animation = m_animations.at(m_current_animation_id);

    if (current_animation.is_looped())
        return false;

    if (current_animation.get_frame_count() == m_current_frame_index + 1)
        return true;

    return false;
}
