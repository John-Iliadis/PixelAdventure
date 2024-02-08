//
// Created by Gianni on 8/02/2024.
//

#include "paper_label.hpp"


void PaperLabel::set_label_texture(const sf::Texture &texture)
{
    m_paper_label.setTexture(texture);
}

void PaperLabel::set_label_position(const sf::Vector2f &pos)
{
    m_paper_label.setPosition(pos);
}

void PaperLabel::set_label_position(float x, float y)
{
    m_paper_label.setPosition(x, y);
}

void PaperLabel::set_label_scale(const sf::Vector2f &scale)
{
    m_paper_label.setScale(scale);
}

void PaperLabel::set_label_scale(float x_factor, float y_factor)
{
    m_paper_label.setScale(x_factor, y_factor);
}

void PaperLabel::set_label_origin(Origin origin)
{
    utils::set_origin(m_paper_label, origin);
}

void PaperLabel::set_text_font(const sf::Font &font)
{
    m_text.setFont(font);
}

void PaperLabel::set_text_string(const std::string &string)
{
    m_text.setString(string);
}

void PaperLabel::set_text_character_size(uint32_t size)
{
    m_text.setCharacterSize(size);
}

void PaperLabel::set_text_color(const sf::Color &color)
{
    m_text.setFillColor(color);
}

void PaperLabel::set_text_offset(const sf::Vector2f &offset)
{
    m_offset = offset;
}

void PaperLabel::set_text_offset(float x, float y)
{
    m_offset = {x, y};
}

bool PaperLabel::is_selectable() const
{
    return false;
}

void PaperLabel::activate()
{
}

void PaperLabel::handle_event(const sf::Event &event)
{
}

sf::Rect<float> PaperLabel::get_clickable_area() const
{
    return m_paper_label.getGlobalBounds();
}

void PaperLabel::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_paper_label, states);

    utils::center_text(m_text);

    auto label_bounds = m_paper_label.getGlobalBounds();

    sf::Vector2i text_pos {
        static_cast<int>(label_bounds.left +  label_bounds.width / 2.f + m_offset.x),
        static_cast<int>(label_bounds.top + label_bounds.height / 2.f + m_offset.y)
    };

    m_text.setPosition(text_pos.x, text_pos.y);

    target.draw(m_text, states);
}
