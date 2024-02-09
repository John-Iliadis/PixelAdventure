//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_GUI_ELEMENT_HPP
#define PLATFORMER_GUI_ELEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>


class GUI_Element : virtual public sf::Drawable
{
public:
    GUI_Element();
    virtual ~GUI_Element() = default;

    virtual bool is_selectable() const = 0;

    virtual void select();
    virtual void deselect();

    virtual void activate() = 0;

    virtual void update(const sf::Vector2i& mouse_pos) = 0;
    virtual void handle_event(const sf::Event& event) = 0;

    virtual sf::Rect<float> get_clickable_area() const = 0;

    bool selected() const;

private:
    bool m_selected;
};


#endif //PLATFORMER_GUI_ELEMENT_HPP
