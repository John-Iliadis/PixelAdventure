//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_NON_LOOPING_ANIMATION_HPP
#define PLATFORMER_NON_LOOPING_ANIMATION_HPP

#include "animation.hpp"


class NonLoopingAnimation : public Animation
{
public:
    NonLoopingAnimation() = default;
    NonLoopingAnimation(uint32_t texture_width, uint32_t texture_height, uint32_t frame_count, sf::Time time_per_frame, bool playing = true);

    void reset() override;
    void update() override;
    bool ended() const;

private:
    bool m_first_play;
    bool m_ended;
};


#endif //PLATFORMER_NON_LOOPING_ANIMATION_HPP
