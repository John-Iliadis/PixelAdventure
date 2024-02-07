//
// Created by Gianni on 6/02/2024.
//

#include <iostream>
#include "button.hpp"

Button::Button()
    : m_button_scale(1, 1)
{
}

void Button::set_position(const sf::Vector2f &pos)
{
    m_button.setPosition(pos);
}

void Button::set_position(float x, float y)
{
    m_button.setPosition(x, y);
}

void Button::set_button_texture(const sf::Texture& texture)
{
    m_button.setTexture(texture);
}

void Button::set_button_origin(Origin origin)
{
    utils::set_origin(m_button, origin);
}

void Button::set_button_scale(const sf::Vector2f &scale)
{
    m_button_scale = scale;
    m_button.setScale(m_button_scale);
}

void Button::set_button_scale(float factor_x, float factor_y)
{
    m_button_scale = {factor_x, factor_y};
    m_button.setScale(m_button_scale);
}

void Button::set_button_callback(std::function<void()> callback)
{
    m_callback = std::move(callback);
}

bool Button::is_selectable() const
{
    return true;
}

sf::Rect<float> Button::get_clickable_area() const
{
    return m_button.getGlobalBounds();
}

void Button::activate()
{
        m_callback? m_callback() : (void)0;
}

void Button::set_button_hover_scale(const sf::Vector2f &scale)
{
    m_button_hover_scale = scale;
}

void Button::set_button_hover_scale(float x_factor, float y_factor)
{
    m_button_hover_scale = {x_factor, y_factor};
}

void Button::select()
{
    if (!selected())
    {
        GUI_Element::select();
        m_button.setScale(m_button_hover_scale);
    }
}

void Button::deselect()
{
    if (selected())
    {
        GUI_Element::deselect();
        m_button.setScale(m_button_scale);
    }
}

void Button::handle_event(const sf::Event &event)
{
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_button, states);
}
