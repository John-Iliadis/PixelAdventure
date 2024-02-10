//
// Created by Gianni on 9/02/2024.
//

#include "slider.hpp"


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
    , m_needs_update(false)
{
    assert(m_value);
    assert(min < max);

    *m_value = std::clamp(*m_value, m_min, m_max);

    utils::set_origin(m_slider_pointer, Origin::CENTER);

    set_slider_pointer();
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
    else if (event.type == sf::Event::MouseMoved && m_dragging)
    {
        sf::Rect<float> slider_bounds = m_slider.getGlobalBounds();
        sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);

        float slider_begin = slider_bounds.left;
        float slider_end = slider_bounds.left + slider_bounds.width;

        float new_pos = std::clamp(mouse_pos.x, slider_begin, slider_end);

        m_slider_pointer.setPosition(new_pos, slider_bounds.top + slider_bounds.height / 2.f);

        *m_value = (new_pos - slider_begin) * (m_min + m_max) / (slider_end - slider_begin);
    }
}

void Slider::update(const sf::Vector2i& mouse_pos)
{
    if (m_needs_update)
    {
        set_slider_pointer();
        m_needs_update = false;
    }
}

sf::Rect<float> Slider::get_clickable_area() const
{
    return m_slider_pointer.getGlobalBounds();
}

void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_slider);
    target.draw(m_slider_pointer);
}

void Slider::set_slider_position(const sf::Vector2f &pos)
{
    m_slider.setPosition(pos);
    m_needs_update = true;
}

void Slider::set_slider_position(float x, float y)
{
    m_slider.setPosition(x, y);
    m_needs_update = true;
}

void Slider::set_slider_scale(const sf::Vector2f &scale)
{
    m_slider.setScale(scale);
    m_slider_pointer.setScale(scale);
    m_needs_update = true;
}

void Slider::set_slider_scale(float x_factor, float y_factor)
{
    m_slider.setScale(x_factor, y_factor);
    m_slider_pointer.setScale(x_factor, y_factor);
    m_needs_update = true;
}

void Slider::set_slider_origin(Origin origin)
{
    utils::set_origin(m_slider, origin);
    m_needs_update = true;
}

void Slider::set_slider_pointer()
{
    auto slider_bounds = m_slider.getGlobalBounds();

    float slider_start = slider_bounds.left;
    float slider_end = slider_bounds.left + slider_bounds.width;

    float position = (*m_value * (slider_end - slider_start) / (m_max + m_min)) + slider_start;

    m_slider_pointer.setPosition(position, slider_bounds.top + slider_bounds.height / 2.f);
}
