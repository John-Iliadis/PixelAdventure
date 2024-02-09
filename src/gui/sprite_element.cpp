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

void SpriteElement::update()
{
}

void SpriteElement::handle_event(const sf::Event &event)
{
}

sf::Rect<float> SpriteElement::get_clickable_area() const
{
    return sf::Rect<float>();
}

void SpriteElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
