//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_ANIMATION_INTERFACE_HPP
#define PLATFORMER_ANIMATION_INTERFACE_HPP

#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "sprite_sheet.hpp"


class IAnimation
{
public:
    virtual ~IAnimation() = default;

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void reset() = 0;

    virtual void update(double dt) = 0;

    virtual const SpriteSheet::Frame& get_current_frame() const = 0;
    virtual const sf::IntRect& get_current_frame_rect() const = 0;
    virtual const std::string& get_current_frame_tag() const = 0;

    virtual bool finished() const = 0;
    virtual bool playing() const = 0;
};


#endif //PLATFORMER_ANIMATION_INTERFACE_HPP
