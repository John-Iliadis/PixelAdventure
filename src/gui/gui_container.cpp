//
// Created by Gianni on 9/02/2024.
//

#include "gui_container.hpp"


void GUI_Container::push_back(std::unique_ptr<GUI_Element> &&gui_component)
{
    m_gui_components.push_back(std::move(gui_component));
}

void GUI_Container::update(const sf::Vector2i& mouse_pos)
{
    for (auto& element : m_gui_components)
    {
        element->update(mouse_pos);
    }
}

void GUI_Container::handle_event(const sf::Event &event)
{
    if (event.type ==  sf::Event::MouseMoved)
    {
        for (auto& element : m_gui_components)
        {
            if (!element->is_selectable()) continue;

            if (element->get_clickable_area().contains(event.mouseMove.x, event.mouseMove.y))
            {
                element->select();
            }
            else
            {
                element->deselect();
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        for (auto& element : m_gui_components)
        {
            if (!element->is_selectable()) continue;

            if (element->get_clickable_area().contains(event.mouseButton.x, event.mouseButton.y))
            {
                element->activate();
            }
        }
    }

    for (auto& element : m_gui_components)
        element->handle_event(event);
}

void GUI_Container::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_container);

    for (const auto& gui_component : m_gui_components)
    {
        target.draw(*gui_component);
    }
}

bool GUI_Container::is_selectable() const
{
    return false;
}

void GUI_Container::activate()
{
}

sf::Rect<float> GUI_Container::get_clickable_area() const
{
    return m_container.getGlobalBounds();
}

void GUI_Container::set_container_texture(const sf::Texture &texture)
{
    m_container.setTexture(texture);
}

void GUI_Container::set_container_position(const sf::Vector2f &pos)
{
    m_container.setPosition(pos);
}

void GUI_Container::set_container_position(float x, float y)
{
    m_container.setPosition(x, y);
}

void GUI_Container::set_container_scale(const sf::Vector2f &scale)
{
    m_container.setScale(scale);
}

void GUI_Container::set_container_scale(float x, float y)
{
    m_container.setScale(x, y);
}

void GUI_Container::set_container_origin(Origin origin)
{
    utils::set_origin(m_container, origin);
}
