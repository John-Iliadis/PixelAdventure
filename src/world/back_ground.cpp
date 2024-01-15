//
// Created by Gianni on 13/01/2024.
//

#include "back_ground.hpp"
#include "iostream"

BackGround::BackGround(TextureManager &texture_manager, const sf::Vector2u& window_size)
    : m_window_size(window_size)
    , scroll_speed(50)
{
    auto& texture = texture_manager.get("Purple");
    texture.setRepeated(true);

    uint32_t texture_height = texture.getSize().x;
    uint32_t sprite_height = window_size.y + (texture_height - window_size.y % texture_height);

    sf::IntRect sprite_rect {
        0, 0,
        static_cast<int>(window_size.x),
        static_cast<int>(sprite_height)
    };

    m_sprites[0].setTexture(texture);
    m_sprites[0].setTextureRect(sprite_rect);

    m_sprites[1] = m_sprites[0];
    m_sprites[1].setPosition(0, m_sprites[0].getGlobalBounds().height);
}

void BackGround::update(double dt)
{
    static bool current = false;

    m_sprites[0].move(0, scroll_speed * dt);
    m_sprites[1].move(0, scroll_speed * dt);

    if (m_sprites[current].getPosition().y > 0)
    {
        current = !current;
        m_sprites[current].setPosition(0, m_sprites[!current].getPosition().y - m_sprites[current].getGlobalBounds().height);
    }
}

void BackGround::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprites[0]);
    target.draw(m_sprites[1]);
}
