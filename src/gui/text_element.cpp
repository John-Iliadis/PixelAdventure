//
// Created by Gianni on 9/02/2024.
//

#include "text_element.hpp"


TextElement::TextElement(const sf::Text &text)
    : m_text(text)
{
}

bool TextElement::is_selectable() const
{
    return false;
}

void TextElement::activate()
{
}

void TextElement::update(const sf::RenderWindow *window)
{

}

void TextElement::handle_event(const sf::Event &event)
{
}

sf::Rect<float> TextElement::get_clickable_area() const
{
    return m_text.getGlobalBounds();
}

void TextElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text);
}
