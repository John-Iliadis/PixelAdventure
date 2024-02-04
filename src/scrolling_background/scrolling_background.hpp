//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_SCROLLING_BACKGROUND_HPP
#define PLATFORMER_SCROLLING_BACKGROUND_HPP

#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../asset_managers/texture_manager.hpp"


class ScrollingBackground : public sf::Drawable
{
public:
    ScrollingBackground() = default;
    ScrollingBackground(sf::Texture& texture, const sf::Vector2i& size);

    void update(double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::array<sf::Sprite, 2> m_scrollable_background;
    static const float m_scroll_speed;
};


#endif //PLATFORMER_SCROLLING_BACKGROUND_HPP
