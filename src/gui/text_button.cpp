//
// Created by Gianni on 6/02/2024.
//

#include "text_button.hpp"

TextButton::TextButton()
    : m_character_size()
    , m_character_size_hover()
{
}

void TextButton::set_text_font(const sf::Font &font)
{
    m_text.setFont(font);
}

void TextButton::set_text_string(const std::string &string)
{
    m_text.setString(string);
}

void TextButton::set_text_character_size(uint32_t size)
{
    m_character_size = size;
    m_text.setCharacterSize(size);
}

void TextButton::set_text_character_size_hover(uint32_t size)
{
    m_character_size_hover = size;
}

void TextButton::set_text_color(const sf::Color &color)
{
    m_text.setFillColor(color);
}

void TextButton::select()
{
    if (!selected())
    {
        GUI_Component::select();
        m_button.setScale(m_button_hover_scale);
        m_text.setCharacterSize(m_character_size_hover);
    }
}

void TextButton::deselect()
{
    if (selected())
    {
        GUI_Component::deselect();
        m_button.setScale(m_button_scale);
        m_text.setCharacterSize(m_character_size);
    }
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    utils::center_text(m_text);

    auto button_bounds = m_button.getGlobalBounds();

    sf::Vector2i text_pos {
        static_cast<int>(button_bounds.left +  button_bounds.width / 2.f),
        static_cast<int>(button_bounds.top + button_bounds.height / 2.f)
    };

    m_text.setPosition(text_pos.x, text_pos.y);

    target.draw(m_button, states);
    target.draw(m_text, states);
}

void TextButton::handle_event(const sf::Event &event)
{
}
