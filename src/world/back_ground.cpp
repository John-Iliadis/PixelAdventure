//
// Created by Gianni on 13/01/2024.
//

#include "back_ground.hpp"


static const float SCROLL_SPEED = 50;

BackGround::BackGround(TextureManager &texture_manager, const sf::Vector2u& map_texture_height)
    : m_scroll_speed(SCROLL_SPEED)
{
    // todo: remove this
    auto size = texture_manager.get("test_map3").getSize();

    auto& texture = texture_manager.get("Purple"); // todo: texture should come from parameter
    texture.setRepeated(true);

    uint32_t texture_height = texture.getSize().y;
    uint32_t sprite_height = size.y + (texture_height - size.y % texture_height);

    sf::IntRect sprite_rect {
        0, 0,
        static_cast<int>(size.x),
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

    m_sprites[0].move(0, m_scroll_speed * dt);
    m_sprites[1].move(0, m_scroll_speed * dt);

    if (m_sprites[current].getPosition().y > 0)
    {
        current = !current;
        m_sprites[current].setPosition(0, int(m_sprites[!current].getPosition().y - m_sprites[current].getGlobalBounds().height));
    }
}

void BackGround::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprites[0]);
    target.draw(m_sprites[1]);
}
