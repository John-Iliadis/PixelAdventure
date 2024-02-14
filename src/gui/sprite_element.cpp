//
// Created by Gianni on 9/02/2024.
//

#include "sprite_element.hpp"


SpriteElement::SpriteElement(const sf::Sprite &sprite)
    : m_sprite(sprite)
{
}

bool SpriteElement::is_selectable() const
{
    return false;
}

void SpriteElement::activate()
{
}

void SpriteElement::handle_event(const sf::Event &event)
{
}

sf::Rect<float> SpriteElement::get_clickable_area() const
{
    return m_sprite.getGlobalBounds();
}

void SpriteElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

sf::Vector2f SpriteElement::get_position() const
{
    return m_sprite.getPosition();
}

void SpriteElement::update(const sf::RenderWindow *window)
{

}
