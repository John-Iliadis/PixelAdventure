//
// Created by Gianni on 15/02/2024.
//

#include "cursor.hpp"


sf::Cursor Cursor::m_arrow;
sf::Cursor Cursor::m_hand;
sf::RenderWindow* Cursor::m_window = nullptr;

void Cursor::init()
{
    m_arrow.loadFromSystem(sf::Cursor::Arrow);
    m_hand.loadFromSystem(sf::Cursor::Hand);
    m_window = nullptr;
}

void Cursor::select_window(sf::RenderWindow *window)
{
    m_window = window;
}

void Cursor::set_cursor(sf::Cursor::Type type)
{
    assert(m_window);

    switch (type)
    {
        case sf::Cursor::Arrow:
            m_window->setMouseCursor(m_arrow);
            break;

        case sf::Cursor::Hand:
            m_window->setMouseCursor(m_hand);
            break;

        default:
            assert(false);
    }
}
