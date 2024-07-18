//
// Created by Gianni on 16/07/2024.
//

#include "gui_button.hpp"


GUI_Button::GUI_Button()
{
    m_text.set_parent(&m_sprite);
}

GUI_Button::GUI_Button(const sf::Texture &texture, const sf::Font &font, uint32_t char_size, sf::String string)
    : m_sprite(texture)
    , m_text(font, char_size, string)
{
    m_text.set_parent(&m_sprite);
}

void GUI_Button::set_texture(const sf::Texture &texture)
{
    m_sprite.set_texture(texture);
}

void GUI_Button::set_font(const sf::Font &font)
{
    m_text.set_font(font);
}

void GUI_Button::set_char_size(uint32_t size)
{
    m_text.set_char_size(size);
}

void GUI_Button::set_string(const sf::String &string)
{
    m_text.set_string(string);
}

void GUI_Button::set_text_color(const sf::Color &color)
{
    m_text.set_color(color);
}

void GUI_Button::set_pos(float x, float y)
{
    m_sprite.set_pos(x, y);
}

void GUI_Button::set_scale(float scale)
{
    m_sprite.set_scale(scale);
}

void GUI_Button::set_origin(float x, float y)
{
    m_sprite.set_origin(x, y);
}

void GUI_Button::handle_event(const sf::Event &event)
{
}

void GUI_Button::draw(sf::RenderWindow &window)
{
    m_sprite.draw(window);
    m_text.draw(window);
}

bool GUI_Button::selectable()
{
    return true;
}

void GUI_Button::activate()
{
    m_callback();
}

sf::FloatRect GUI_Button::local_bb() const
{
    return m_sprite.local_bb();
}

sf::FloatRect GUI_Button::global_bb() const
{
    return transform().transformRect(local_bb());
}

sf::Transform GUI_Button::transform() const
{
    return m_sprite.transform();
}

void GUI_Button::select()
{
    if (!selected())
    {
        GUI_Element::select();
    }
}

void GUI_Button::deselect()
{
    if (selected())
    {
        GUI_Element::deselect();
    }
}
