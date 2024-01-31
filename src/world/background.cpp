//
// Created by Gianni on 13/01/2024.
//

#include "background.hpp"


static const float SCROLL_SPEED = 50;

BackGround::BackGround(TextureManager &texture_manager)
    : m_scroll_speed(SCROLL_SPEED)
{
    m_map.setTexture(texture_manager.get("test_map3"));

    sf::Vector2u map_size = static_cast<sf::Vector2u>(m_map.getGlobalBounds().getSize());

    sf::Texture& texture = texture_manager.get("Purple"); // todo: texture should come from parameter
    texture.setRepeated(true);

    uint32_t texture_height = texture.getSize().y;
    uint32_t sprite_height = map_size.y + (texture_height - map_size.y % texture_height);

    sf::IntRect sprite_rect {
        0, 0,
        static_cast<int>(map_size.x),
        static_cast<int>(sprite_height)
    };

    m_scrollable_background[0].setTexture(texture);
    m_scrollable_background[0].setTextureRect(sprite_rect);

    m_scrollable_background[1] = m_scrollable_background[0];
    m_scrollable_background[1].setPosition(0, m_scrollable_background[0].getGlobalBounds().height);
}

void BackGround::update(double dt)
{
    static bool current = false;

    m_scrollable_background[0].move(0, m_scroll_speed * dt);
    m_scrollable_background[1].move(0, m_scroll_speed * dt);

    if (m_scrollable_background[current].getPosition().y > 0)
    {
        current = !current;
        m_scrollable_background[current].setPosition(0, int(m_scrollable_background[!current].getPosition().y - m_scrollable_background[current].getGlobalBounds().height));
    }
}

void BackGround::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_scrollable_background[0]);
    target.draw(m_scrollable_background[1]);
    target.draw(m_map);
}
