//
// Created by Gianni on 6/02/2024.
//

#include <iostream>
#include "gui_button_base.hpp"

GUI_Button_Base::GUI_Button_Base()
    : m_button_scale(1, 1)
{
}

void GUI_Button_Base::set_position(const sf::Vector2f &pos)
{
    m_button.setPosition(pos);
}

void GUI_Button_Base::set_position(float x, float y)
{
    m_button.setPosition(x, y);
}

void GUI_Button_Base::set_button_texture(const sf::Texture& texture)
{
    m_button.setTexture(texture);
}

void GUI_Button_Base::set_button_origin(Origin origin)
{
    utils::set_origin(m_button, origin);
}

void GUI_Button_Base::set_button_scale(const sf::Vector2f &scale)
{
    m_button_scale = scale;
    m_button.setScale(m_button_scale);
}

void GUI_Button_Base::set_button_scale(float factor_x, float factor_y)
{
    m_button_scale = {factor_x, factor_y};
    m_button.setScale(m_button_scale);
}

void GUI_Button_Base::set_button_callback(std::function<void()> callback)
{
    m_callback = std::move(callback);
}

bool GUI_Button_Base::is_selectable() const
{
    return true;
}

sf::Rect<float> GUI_Button_Base::get_clickable_area() const
{
    return m_button.getGlobalBounds();
}

void GUI_Button_Base::activate()
{
    if (!active())
    {
        GUI_Component::activate();
        m_callback? m_callback() : (void)0;
    }
}

void GUI_Button_Base::deactivate()
{
    if (active())
    {
        GUI_Component::deactivate();
    }
}

void GUI_Button_Base::set_button_hover_scale(const sf::Vector2f &scale)
{
    m_button_hover_scale = scale;
}

void GUI_Button_Base::set_button_hover_scale(float x_factor, float y_factor)
{
    m_button_hover_scale = {x_factor, y_factor};
}
