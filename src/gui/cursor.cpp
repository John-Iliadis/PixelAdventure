//
// Created by Gianni on 15/02/2024.
//

#include "cursor.hpp"


sf::Cursor Cursor::m_arrow;
sf::Cursor Cursor::m_hand;
sf::RenderWindow* Cursor::m_window = nullptr;
bool Cursor::m_item_selected = false;


void Cursor::init()
{
    m_arrow.loadFromSystem(sf::Cursor::Arrow);
    m_hand.loadFromSystem(sf::Cursor::Hand);
}

void Cursor::select_window(sf::RenderWindow *window)
{
    m_window = window;
}

void Cursor::set_cursor()
{
    assert(m_window);

    m_window->setMouseCursor(m_item_selected? m_hand : m_arrow);
}

void Cursor::set_item_selected(bool selected)
{
    m_item_selected = selected;
}

bool Cursor::item_selected()
{
    return m_item_selected;
}

sf::Vector2f Cursor::get_mouse_pos()
{
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));
}
