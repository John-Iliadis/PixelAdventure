//
// Created by Gianni on 7/02/2024.
//

#ifndef PLATFORMER_GUI_CONTAINER_HPP
#define PLATFORMER_GUI_CONTAINER_HPP

#include <functional>
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Cursor.hpp>
#include "gui_element.hpp"


class GUI_Container : public sf::Drawable
{
public:
    GUI_Container() = default;

    void push_back(std::unique_ptr<GUI_Element>&& gui_component);

    void handle_events(const sf::Event& event);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<std::unique_ptr<GUI_Element>> m_gui_components;
};


#endif //PLATFORMER_GUI_CONTAINER_HPP
