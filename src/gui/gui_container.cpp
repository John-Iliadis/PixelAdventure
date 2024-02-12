//
// Created by Gianni on 9/02/2024.
//

#include "gui_container.hpp"


void GUI_Container::push_back(std::unique_ptr<GUI_Element> &&gui_component)
{
    m_gui_components.push_back(std::move(gui_component));
}

void GUI_Container::update()
{
    for (auto& element : m_gui_components)
    {
        element->update();
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
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
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
    return sf::Rect<float>();
}

GUI_Container::iterator GUI_Container::begin()
{
    return m_gui_components.begin();
}

GUI_Container::iterator GUI_Container::end()
{
    return m_gui_components.end();
}
