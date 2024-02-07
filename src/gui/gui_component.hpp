//
// Created by Gianni on 6/02/2024.
//

#ifndef PLATFORMER_GUI_COMPONENT_HPP
#define PLATFORMER_GUI_COMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>


class GUI_Component : public sf::Drawable
{
public:
    GUI_Component();
    virtual ~GUI_Component() = default;

    virtual bool is_selectable() const = 0;

    virtual void select();
    virtual void deselect();

    virtual void activate();
    virtual void deactivate();

    virtual void handle_event(const sf::Event& event) = 0;

    virtual sf::Rect<float> get_clickable_area() const = 0;

    bool selected() const;
    bool active() const;

private:
    bool m_selected;
    bool m_active;
};


#endif //PLATFORMER_GUI_COMPONENT_HPP
