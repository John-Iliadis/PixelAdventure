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

GUI_Slider::GUI_Slider(const sf::Texture &slider_tex, const sf::Texture &slider_ptr_tex)
    : GUI_Slider()
{
    set_textures(slider_tex, slider_ptr_tex);
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
    m_slider_ptr.set_origin(Origin::CENTER);
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
        if (bounding_box().contains(event.mouseButton.x, event.mouseButton.y))
            m_dragging = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        m_dragging = false;
    }
    else if (m_dragging && event.type == sf::Event::MouseMoved)
    {
        sf::FloatRect slider_bb(m_slider.bounding_box());
        sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);

        float left = slider_bb.left;
        float right = left + slider_bb.width;

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
    sf::FloatRect slider_bb(m_slider.bounding_box());

    float left = slider_bb.left;
    float right = left + slider_bb.width;

    float x_pos = (*m_value * (right - left) / (m_min + m_max)) + left;
    float y_pos = slider_bb.top + slider_bb.height / 2.f;

    m_slider_ptr.set_pos_glob(x_pos, y_pos);
}

void GUI_Slider::set_pos_rel(float x, float y)
{
    m_slider.set_pos_rel(x, y);
    set_slider_ptr();
}

void GUI_Slider::set_pos_glob(float x, float y)
{
    m_slider.set_pos_glob(x, y);
    set_slider_ptr();
}

void GUI_Slider::set_scale(float scale)
{
    m_slider.set_scale(scale);
    set_slider_ptr();
}

void GUI_Slider::set_origin(Origin origin)
{
    m_slider.set_origin(origin);
    set_slider_ptr();
}

void GUI_Slider::set_parent(GUI_Element *parent)
{
    m_slider.set_parent(parent);
}

sf::FloatRect GUI_Slider::bounding_box() const
{
    return m_slider_ptr.bounding_box();
}
