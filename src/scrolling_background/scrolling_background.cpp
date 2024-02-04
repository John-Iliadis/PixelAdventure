//
// Created by Gianni on 13/01/2024.
//

#include "scrolling_background.hpp"


const float ScrollingBackground::m_scroll_speed = 50;

ScrollingBackground::ScrollingBackground(sf::Texture& texture, const sf::Vector2i &size)
{
    texture.setRepeated(true);

    sf::Vector2i texture_size = static_cast<sf::Vector2i>(texture.getSize());

    sf::Vector2i bg_size {
        size.x,
        size.y + (texture_size.y - size.y % texture_size.y)
    };

    sf::Rect<int> sprite_rect {{0, 0}, bg_size};

    m_scrollable_background.front().setTexture(texture);
    m_scrollable_background.front().setTextureRect(sprite_rect);

    m_scrollable_background.back() = m_scrollable_background.front();
    m_scrollable_background.back().setPosition(0, m_scrollable_background.front().getGlobalBounds().height);
}

void ScrollingBackground::update(double dt)
{
    float move_speed = m_scroll_speed * dt;

    m_scrollable_background.front().move(0, move_speed);
    m_scrollable_background.back().move(0, move_speed);

    if (m_scrollable_background.front().getPosition().y > 0)
    {
        sf::Vector2f new_pos(0, m_scrollable_background.front().getPosition().y - m_scrollable_background.front().getGlobalBounds().height);

        m_scrollable_background.back().setPosition(new_pos);

        std::swap(m_scrollable_background.front(), m_scrollable_background.back());
    }
}

void ScrollingBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_scrollable_background.front());
    target.draw(m_scrollable_background.back());
}
