//
// Created by Gianni on 13/02/2024.
//

#include "gui_utils.hpp"


namespace utils::gui
{
    void select_element(GUI_Container& gui_container, const sf::RenderWindow* relative_window)
    {
        sf::Vector2i mouse_pos = relative_window? sf::Mouse::getPosition(*relative_window) : sf::Mouse::getPosition();

        for (auto& element : gui_container)
        {
            if (!element->is_selectable()) continue;

            if (element->get_clickable_area().contains(mouse_pos.x, mouse_pos.y))
            {
                element->select();
                return;
            }
        }
    }

    void deselect_all_elements(GUI_Container& gui_container)
    {
        for (auto& element : gui_container)
        {
            if (!element->is_selectable()) continue;

            element->deselect();
        }
    }
}
