//
// Created by Gianni on 22/01/2024.
//

#include "animation_manager.hpp"
#include <iostream>


AnimationManager::AnimationManager(const std::string &file_name)
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
    }

    nlohmann::json json = nlohmann::json::parse(file);

    file.close();

    int width = json["sprite_width"].get<int>();
    int height = json["sprite_height"].get<int>();

    for (const auto& animation : json["animations"])
    {
        SpriteSheet l_sprite_sheet {
            width,
            height,
            animation["frame_count"].get<uint32_t>()
        };

        std::string id = animation["id"].get<std::string>();

        if (animation.contains("tags"))
        {
            for (const auto& tag : animation["tags"])
            {
                size_t index = tag["index"].get<size_t>();
                std::string value = tag["value"].get<std::string>();

                l_sprite_sheet.set_frame_tag(index, value);
            }
        }

        Animation l_animation {
            std::move(l_sprite_sheet),
            sf::milliseconds(animation["frame_time_milliseconds"].get<int>()),
            animation["looped"].get<bool>()
        };

        m_animations.emplace(std::make_pair(std::move(id), std::move(l_animation)));
    }
}

void AnimationManager::add_animation(std::pair<std::string, Animation>&& animation)
{
    m_animations.emplace(animation);
}

void AnimationManager::play()
{
    m_animations[m_current_animation_id].play();
}

void AnimationManager::pause()
{
    m_animations[m_current_animation_id].pause();
}

void AnimationManager::reset()
{
    m_animations[m_current_animation_id].reset();
}

void AnimationManager::set_animation(const std::string& id)
{
    assert(m_animations.find(id) != m_animations.end());

    m_current_animation_id = id;
    m_animations[m_current_animation_id].reset();
    m_animations[m_current_animation_id].play();
}

void AnimationManager::update(double dt)
{
    assert(!m_animations.empty() && !m_current_animation_id.empty());

    if (!m_animations[m_current_animation_id].playing()) return;

    m_animations[m_current_animation_id].update(dt);
}

const SpriteSheet::Frame& AnimationManager::get_current_frame() const
{
    return m_animations.at(m_current_animation_id).get_current_frame();
}

const sf::IntRect &AnimationManager::get_current_frame_rect() const
{
    return m_animations.at(m_current_animation_id).get_current_frame_rect();
}

const std::string &AnimationManager::get_current_frame_tag() const
{
    return m_animations.at(m_current_animation_id).get_current_frame_tag();
}

bool AnimationManager::finished() const
{
    return m_animations.at(m_current_animation_id).finished();
}

bool AnimationManager::playing() const
{
    return m_animations.at(m_current_animation_id).playing();
}
