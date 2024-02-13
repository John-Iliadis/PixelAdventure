//
// Created by Gianni on 13/02/2024.
//

#ifndef PLATFORMER_GUI_UTILS_HPP
#define PLATFORMER_GUI_UTILS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../gui/gui_container.hpp"


namespace utils::gui
{
    void select_element(GUI_Container& gui_container, const sf::RenderWindow* relative_window = nullptr);

    void deselect_all_elements(GUI_Container& gui_container);
}


#endif //PLATFORMER_GUI_UTILS_HPP
