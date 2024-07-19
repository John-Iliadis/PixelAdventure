//
// Created by Gianni on 15/07/2024.
//

#include "gui_element.hpp"


GUI_Element::GUI_Element()
    : m_parent()
    , m_selected()
{
}

void GUI_Element::select()
{
    m_selected = true;
}

void GUI_Element::deselect()
{
    m_selected = false;
}

bool GUI_Element::selected() const
{
    return m_selected;
}

void GUI_Element::set_parent(GUI_Element *parent)
{
    m_parent = parent;
}

//sf::Transform GUI_Element::global_transform() const
//{
//    if (m_parent)
//    {
//        return m_parent->global_transform() * transform();
//    }
//
//    return transform();
//}
