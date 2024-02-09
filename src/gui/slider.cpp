//
// Created by Gianni on 9/02/2024.
//

#include "slider.hpp"

#include <iostream>

Slider::Slider()
    : m_value(nullptr)
    , m_dragging(false)
{
}

Slider::Slider(const TextureManager &textures, float *value, float min, float max)
    : m_slider(textures.get("slider"))
    , m_slider_pointer(textures.get("slider_pointer"))
    , m_value(value)
    , m_min(min)
    , m_max(max)
    , m_dragging(false)
{
    assert(m_value);
    assert(min < max);

    set_value(*m_value);

    utils::set_origin(m_slider_pointer, Origin::CENTER);
}

bool Slider::is_selectable() const
{
    return false;
}

void Slider::activate()
{
}

void Slider::handle_event(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (m_slider_pointer.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            m_dragging = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        m_dragging = false;
    }
}

void Slider::update(const sf::Vector2i& mouse_pos)
{
    if (m_dragging)
    {
        auto slider_bounds = m_slider.getGlobalBounds();

        float x = slider_bounds.left;

        float new_value = (mouse_pos.x - x) / slider_bounds.width;

        set_value(new_value);
    }
}

void Slider::set_value(float new_value)
{
    float normalized_value = std::clamp(new_value, 0.f, 1.f);

    auto slider_bounds = m_slider.getGlobalBounds();

    float x = slider_bounds.left;
    float y = slider_bounds.top + slider_bounds.height / 2.f;

    m_slider_pointer.setPosition(x + normalized_value * slider_bounds.width, y);

    *m_value = m_min + (normalized_value * (m_max - m_min));
}

sf::Rect<float> Slider::get_clickable_area() const
{
    return sf::Rect<float>();
}

void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_slider);
    target.draw(m_slider_pointer);
}

void Slider::set_slider_position(const sf::Vector2f &pos)
{
    m_slider.setPosition(pos);
    set_value(*m_value);

}

void Slider::set_slider_position(float x, float y)
{
    m_slider.setPosition(x, y);
    set_value(*m_value);
}

void Slider::set_slider_scale(const sf::Vector2f &scale)
{
    m_slider.setScale(scale);
    m_slider_pointer.setScale(scale);
}

void Slider::set_slider_scale(float x_factor, float y_factor)
{
    m_slider.setScale(x_factor, y_factor);
    m_slider_pointer.setScale(x_factor, y_factor);
}

void Slider::set_slider_origin(Origin origin)
{
    utils::set_origin(m_slider, origin);
}
