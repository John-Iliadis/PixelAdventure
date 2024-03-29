//
// Created by Gianni on 9/02/2024.
//

#include "gui_element.hpp"


GUI_Element::GUI_Element()
    : m_selected(false)
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
