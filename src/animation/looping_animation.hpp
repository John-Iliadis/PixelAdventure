//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_LOOPING_ANIMATION_HPP
#define PLATFORMER_LOOPING_ANIMATION_HPP

#include <SFML/System/Clock.hpp>
#include "animation.hpp"


class LoopingAnimation : public Animation
{
public:
    LoopingAnimation() = default;
    LoopingAnimation(uint32_t texture_width, uint32_t texture_height, uint32_t frame_count, sf::Time time_per_frame, bool playing = true);

    void update() override;
};


#endif //PLATFORMER_LOOPING_ANIMATION_HPP
