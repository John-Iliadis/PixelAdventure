//
// Created by Gianni on 15/02/2024.
//

#ifndef PLATFORMER_CURSOR_HPP
#define PLATFORMER_CURSOR_HPP

#include <cassert>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>


class Cursor
{
public:
    static void init();
    static void select_window(sf::RenderWindow* window);
    static void set_cursor(sf::Cursor::Type type);

private:
    static sf::Cursor m_arrow;
    static sf::Cursor m_hand;
    static sf::RenderWindow* m_window;
};


#endif //PLATFORMER_CURSOR_HPP
