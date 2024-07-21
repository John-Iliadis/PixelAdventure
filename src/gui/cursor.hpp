//
// Created by Gianni on 15/02/2024.
//

#ifndef PLATFORMER_CURSOR_HPP
#define PLATFORMER_CURSOR_HPP

#include <cassert>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Mouse.hpp>


class Cursor
{
public:
    static void init();
    static void select_window(sf::RenderWindow* window);
    static void set_cursor();
    static void set_item_selected(bool selected);
    static bool item_selected();
    static sf::Vector2f get_mouse_pos();

private:
    static sf::Cursor m_arrow;
    static sf::Cursor m_hand;
    static sf::RenderWindow* m_window;
    static bool m_item_selected;
};


#endif //PLATFORMER_CURSOR_HPP
