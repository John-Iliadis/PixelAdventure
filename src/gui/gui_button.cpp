//
// Created by Gianni on 16/07/2024.
//

#include "gui_button.hpp"
#include "../audio/sound_player.hpp"


GUI_Button::GUI_Button()
{
    m_text.set_parent(&m_sprite);
}

GUI_Button::GUI_Button(const sf::Texture &texture, const sf::Font &font, uint32_t char_size, sf::String string)
    : m_sprite(texture)
    , m_text(font, char_size, string)
{
    m_text.set_parent(&m_sprite);
    set_text_pos();
}

void GUI_Button::set_texture(const sf::Texture &texture)
{
    m_sprite.set_texture(texture);
    set_text_pos();
}

void GUI_Button::set_font(const sf::Font &font)
{
    m_text.set_font(font);
    set_text_pos();
}

void GUI_Button::set_char_size(uint32_t size)
{
    m_text.set_char_size(size);
    set_text_pos();
}

void GUI_Button::set_string(const sf::String &string)
{
    m_text.set_string(string);
    set_text_pos();
}

void GUI_Button::set_text_color(const sf::Color &color)
{
    m_text.set_color(color);
}

void GUI_Button::set_text_offset(float x, float y)
{
    m_text_offset = {x, y};
}

void GUI_Button::set_pos_rel(float x, float y)
{
    m_sprite.set_pos_rel(x, y);
    set_text_pos();
}

void GUI_Button::set_pos_glob(float x, float y)
{
    m_sprite.set_pos_glob(x, y);
    set_text_pos();
}

void GUI_Button::set_scale(float scale)
{
    m_sprite.set_scale(scale);
    set_text_pos();
}

void GUI_Button::set_text_scale(float scale)
{
    m_text.set_scale(scale);
}

void GUI_Button::set_origin(Origin origin)
{
    m_sprite.set_origin(origin);
    set_text_pos();
}

void GUI_Button::set_callback(std::function<void()> callback)
{
    m_callback = callback;
}

void GUI_Button::set_parent(GUI_Element *parent)
{
    m_sprite.set_parent(parent);
}

void GUI_Button::handle_event(const sf::Event &event)
{
}

void GUI_Button::update()
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
    SoundPlayer::play_sound("button_click");
    m_callback();
}

sf::FloatRect GUI_Button::bounding_box() const
{
    return m_sprite.bounding_box();
}

void GUI_Button::set_text_pos()
{
    const auto [width, height] = bounding_box().getSize();

    m_text.set_origin(Origin::CENTER);
    m_text.set_pos_rel(width / 2.f + m_text_offset.x, height / 2.f + m_text_offset.y);
}
