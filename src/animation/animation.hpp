//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_ANIMATION_HPP
#define PLATFORMER_ANIMATION_HPP

#include <SFML/System/NonCopyable.hpp>
#include "sprite_sheet.hpp"
#include "animation_interface.hpp"


class Animation : public IAnimation
{
public:
    Animation();
    Animation(int sprite_width, int sprite_height, uint32_t frame_count, sf::Time time_per_frame, bool looped = true);
    Animation(SpriteSheet&& sprite_sheet, sf::Time time_per_frame, bool looped = true);

    Animation(const Animation& other) noexcept;
    Animation& operator=(const Animation& other) noexcept;

    Animation(Animation&&) noexcept = default;
    Animation& operator=(Animation&&) noexcept = default;

    void play() override;
    void pause() override;
    void reset() override;

    void update(double dt) override;

    const SpriteSheet::Frame& get_current_frame() const override;
    const sf::IntRect& get_current_frame_rect() const override;
    const std::string& get_current_frame_tag() const override;

    bool finished() const override;
    bool playing() const override;

private:
    SpriteSheet m_sprite_sheet;
    SpriteSheet::Frame m_current_frame;
    size_t m_frame_index;
    sf::Time m_ellapsed;
    sf::Time m_time_per_frame;
    bool m_playing;
    bool m_looped;
};


#endif //PLATFORMER_ANIMATION_HPP
