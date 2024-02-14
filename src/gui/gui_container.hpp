//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_GUI_CONTAINER_HPP
#define PLATFORMER_GUI_CONTAINER_HPP


#include <functional>
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "gui_element.hpp"
#include "../enums/origin.hpp"
#include "../utilities/utils.hpp"
#include "../world/cursor.hpp"


class GUI_Container : public GUI_Element
{
public:
    GUI_Container() = default;

    void push_back(std::unique_ptr<GUI_Element>&& gui_component);

    void activate() override;

    void update(const sf::RenderWindow *window) override;
    void handle_event(const sf::Event &event) override;

    void find_selected(const sf::RenderWindow* relative_window = nullptr);
    void deselect_all();

    sf::Rect<float> get_clickable_area() const override;
    bool is_selectable() const override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<std::unique_ptr<GUI_Element>> m_gui_elements;
};


#endif //PLATFORMER_GUI_CONTAINER_HPP
