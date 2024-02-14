//
// Created by Gianni on 9/02/2024.
//

#include "gui_container.hpp"


void GUI_Container::push_back(std::unique_ptr<GUI_Element> &&gui_component)
{
    m_gui_elements.push_back(std::move(gui_component));
}

void GUI_Container::update(const sf::RenderWindow *window)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);

    bool set_cursor_hand = false;

    for (auto& element : m_gui_elements)
    {
        element->update(window);

        if (!element->is_selectable()) continue;

        if (element->get_clickable_area().contains(mouse_pos.x, mouse_pos.y))
            set_cursor_hand = true;
    }

    Cursor::set_cursor(set_cursor_hand? sf::Cursor::Hand : sf::Cursor::Arrow);
}

void GUI_Container::handle_event(const sf::Event &event)
{
    if (event.type ==  sf::Event::MouseMoved)
    {
        for (auto& element : m_gui_elements)
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
        for (auto& element : m_gui_elements)
        {
            if (!element->is_selectable()) continue;

            if (element->get_clickable_area().contains(event.mouseButton.x, event.mouseButton.y))
            {
                element->activate();
            }
        }
    }

    for (auto& element : m_gui_elements)
        element->handle_event(event);
}

void GUI_Container::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& gui_component : m_gui_elements)
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

void GUI_Container::deselect_all()
{
    for (auto& element : m_gui_elements)
    {
        if (!element->is_selectable()) continue;

        element->deselect();
    }

    Cursor::set_cursor(sf::Cursor::Arrow);
}

void GUI_Container::find_selected(const sf::RenderWindow *relative_window)
{
    sf::Vector2i mouse_pos = relative_window? sf::Mouse::getPosition(*relative_window) : sf::Mouse::getPosition();

    for (auto& element : m_gui_elements)
    {
        if (!element->is_selectable()) continue;

        if (element->get_clickable_area().contains(mouse_pos.x, mouse_pos.y))
        {
            element->select();
            Cursor::set_cursor(sf::Cursor::Hand);
            return;
        }
    }
}

