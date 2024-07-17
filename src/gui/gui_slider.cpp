//
// Created by Gianni on 16/07/2024.
//

#include "gui_slider.hpp"


GUI_Slider::GUI_Slider()
    : m_value()
    , m_min()
    , m_max()
    , m_dragging()
{
    m_slider_ptr.set_parent(&m_slider);
}

GUI_Slider::GUI_Slider(const sf::Texture &slider_tex,
                       const sf::Texture &slider_ptr_tex,
                       float *value, float min, float max)
    : GUI_Slider()
{
    set_textures(slider_tex, slider_ptr_tex);
    set_value(value, min, max);
    set_slider_ptr();
}

void GUI_Slider::set_textures(const sf::Texture &slider_tex, const sf::Texture &slider_ptr_tex)
{
    m_slider.set_texture(slider_tex);
    m_slider_ptr.set_texture(slider_ptr_tex);

    auto [width, height] = m_slider_ptr.local_bb().getSize();
    m_slider_ptr.set_origin(width / 2.f, height / 2.f);
}

void GUI_Slider::set_value(float *value, float min, float max)
{
    assert(value);
    assert(*value > min && *value < max);

    m_value = value;
    m_min = min;
    m_max = max;

    set_slider_ptr();
}

void GUI_Slider::handle_event(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (global_bb().contains(event.mouseButton.x, event.mouseButton.y))
            m_dragging = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        m_dragging = false;
    }
    else if (m_dragging && event.type == sf::Event::MouseMoved)
    {
        sf::FloatRect slider_bb(m_slider.global_bb());
        sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);

        float left = slider_bb.left;
        float right = slider_bb.left + slider_bb.width;

        float new_pos = std::clamp(mouse_pos.x, left, right);

        *m_value = (new_pos - left) / (right - left) * (m_min + m_max);

        set_slider_ptr();
    }
}

void GUI_Slider::draw(sf::RenderWindow &window)
{
    m_slider.draw(window);
    m_slider_ptr.draw(window);
}

bool GUI_Slider::selectable()
{
    return false;
}

void GUI_Slider::activate()
{
}

void GUI_Slider::set_slider_ptr()
{
    auto [width, height] = m_slider.local_bb().getSize();

    float x_pos = *m_value * width / (m_min + m_max);
    float y_pos = height / 2.f;

    m_slider_ptr.set_pos(x_pos, y_pos);
}

void GUI_Slider::set_pos(float x, float y)
{
    m_slider.set_pos(x, y);
}

void GUI_Slider::set_scale(float scale)
{
    m_slider.set_scale(scale);
}

void GUI_Slider::set_origin(float x, float y)
{
    m_slider.set_origin(x, y);
}

sf::FloatRect GUI_Slider::local_bb() const
{
    return m_slider.local_bb(); // local gives slider
}

sf::FloatRect GUI_Slider::global_bb() const
{
    return m_slider_ptr.global_bb(); // global gives ptr for mouse check
}

sf::Transform GUI_Slider::transform() const
{
    return m_slider.transform();
}

void GUI_Slider::set_parent(GUI_Element *parent)
{
    m_slider.set_parent(parent);
}
