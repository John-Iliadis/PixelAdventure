//
// Created by Gianni on 16/07/2024.
//

#include "gui_container.hpp"


GUI_Container::GUI_Container(const sf::Texture &texture)
    : m_sprite(texture)
{
}

GUI_Container::~GUI_Container()
{
    std::for_each(m_elements.begin(), m_elements.end(), [] (auto e) { delete e; });
}

void GUI_Container::pack(GUI_Element* gui_element)
{
    gui_element->set_parent(&m_sprite);
    m_elements.push_back(gui_element);
}

void GUI_Container::set_texture(const sf::Texture &texture)
{
    m_sprite.set_texture(texture);
}

void GUI_Container::set_pos_rel(float x, float y)
{
    m_sprite.set_pos_rel(x, y);
}

void GUI_Container::set_pos_glob(float x, float y)
{
    m_sprite.set_pos_glob(x, y);
}

void GUI_Container::set_scale(float scale)
{
    m_sprite.set_scale(scale);
}

void GUI_Container::set_origin(Origin origin)
{
    m_sprite.set_origin(origin);
}

void GUI_Container::set_parent(GUI_Element *parent)
{
    m_sprite.set_parent(parent);
}

void GUI_Container::handle_event(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        for (auto element : m_elements)
        {
            if (!element->selectable())
                continue;

            if (element->bounding_box().contains(event.mouseMove.x, event.mouseMove.y))
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
        for (auto element : m_elements)
        {
            if (!element->selectable())
                continue;

            if (element->bounding_box().contains(event.mouseButton.x, event.mouseButton.y))
            {
                element->activate();
            }
        }
    }

    for (auto element : m_elements)
        element->handle_event(event);
}

void GUI_Container::draw(sf::RenderWindow &window)
{
    m_sprite.draw(window);

    for (auto element : m_elements)
        element->draw(window);
}

bool GUI_Container::selectable()
{
    return false;
}

void GUI_Container::activate()
{
}

sf::FloatRect GUI_Container::bounding_box() const
{
    return m_sprite.bounding_box();
}
