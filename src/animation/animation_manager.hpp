//
// Created by Gianni on 22/01/2024.
//

#ifndef PLATFORMER_ANIMATION_MANAGER_HPP
#define PLATFORMER_ANIMATION_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include "animation.hpp"
#include "../vendor/json.hpp"


class AnimationManager
{
public:
    AnimationManager();
    AnimationManager(const std::string& file_name);

    void load_from_file(const std::string& file_name);
    void add_animation(std::pair<std::string, Animation>&& animation);

    void play();
    void pause();
    void reset();

    void set_animation(const std::string& id);
    void update(double dt);

    const Animation::Frame& get_current_frame() const;
    const sf::IntRect& get_current_frame_rect() const;
    const std::string& get_current_frame_tag() const;

private:
    std::unordered_map<std::string, Animation> m_animations;
    std::string m_current_animation_id;
    size_t m_current_frame_index;
    sf::Time m_ellapsed;
    bool m_playing;
};


#endif //PLATFORMER_ANIMATION_MANAGER_HPP
