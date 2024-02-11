//
// Created by Gianni on 9/02/2024.
//

#include "text_button.hpp"


TextButton::TextButton()
    : m_offset()
{
}

void TextButton::set_text_font(const sf::Font &font)
{
    m_text.setFont(font);
    m_selected_text.setFont(font);
}

void TextButton::set_text_string(const std::string &string)
{
    m_text.setString(string);
    m_selected_text.setString(string);
}

void TextButton::set_text_character_size(uint32_t size)
{
    m_text.setCharacterSize(size);
}

void TextButton::set_text_character_size_hover(uint32_t size)
{
    m_selected_text.setCharacterSize(size);
}

void TextButton::set_text_color(const sf::Color &color)
{
    m_text.setFillColor(color);
    m_selected_text.setFillColor(color);
}

void TextButton::update()
{
    utils::set_origin(m_text, Origin::CENTER);
    utils::set_origin(m_selected_text, Origin::CENTER);

    auto button_bounds = m_button.getGlobalBounds();

    sf::Vector2i text_pos {
            static_cast<int>(button_bounds.left +  button_bounds.width / 2.f + m_offset.x),
            static_cast<int>(button_bounds.top + button_bounds.height / 2.f + m_offset.y)
    };

    m_text.setPosition(text_pos.x, text_pos.y);
    m_selected_text.setPosition(text_pos.x, text_pos.y);
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_button);

    target.draw(selected()? m_selected_text : m_text);
}

void TextButton::set_text_offset(const sf::Vector2f &offset)
{
    m_offset = offset;
}

void TextButton::set_text_offset(float x, float y)
{
    m_offset = {x, y};
}

void TextButton::handle_event(const sf::Event &event)
{
}
