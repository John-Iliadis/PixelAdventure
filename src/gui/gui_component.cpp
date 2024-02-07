//
// Created by Gianni on 6/02/2024.
//

#include "gui_component.hpp"

GUI_Component::GUI_Component()
    : m_selected(false)
    , m_active(false)
{
}

void GUI_Component::select()
{
    m_selected = true;
}

void GUI_Component::deselect()
{
    m_selected = false;
}

bool GUI_Component::selected() const
{
    return m_selected;
}

void GUI_Component::activate()
{
    m_active = true;
}

void GUI_Component::deactivate()
{
    m_active = false;
}

bool GUI_Component::active() const
{
    return m_active;
}
