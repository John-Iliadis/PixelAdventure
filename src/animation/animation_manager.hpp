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
#include "../vendor/json.hpp"
#include "animation.hpp"


class AnimationManager : public IAnimation
{
public:
    AnimationManager() = default;
    AnimationManager(const std::string& file_name);

    void load_from_file(const std::string& file_name);
    void add_animation(std::pair<std::string, Animation>&& animation);

    void play() override;
    void pause() override;
    void reset() override;

    void set_animation(const std::string& id);
    void update(double dt) override;

    const SpriteSheet::Frame& get_current_frame() const override;
    const sf::IntRect& get_current_frame_rect() const override;
    const std::string& get_current_frame_tag() const override;

    bool finished() const override;
    bool playing() const override;

private:
    std::unordered_map<std::string, Animation> m_animations;
    std::string m_current_animation_id;
};


#endif //PLATFORMER_ANIMATION_MANAGER_HPP
