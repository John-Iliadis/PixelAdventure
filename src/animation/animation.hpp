//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_ANIMATION_HPP
#define PLATFORMER_ANIMATION_HPP

#include <vector>
#include <cstdint>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>


class Animation
{
public:
    Animation();
    Animation(uint32_t texture_width, uint32_t texture_height, uint32_t frame_count, sf::Time time_per_frame, bool playing = false);
    virtual ~Animation() = default;

    virtual void start();
    virtual void stop();
    virtual void reset();

    virtual void update(sf::Sprite& sprite) = 0;

    const sf::Rect<uint32_t>& get_current_frame() const;

protected:
    std::vector<sf::Rect<uint32_t>> m_frames;
    sf::Clock m_clock;
    sf::Time m_time_pre_frame;
    uint32_t m_frame_count;
    uint32_t m_frame_index;
    bool m_playing;
};


#endif //PLATFORMER_ANIMATION_HPP
