//
// Created by Gianni on 15/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_ELEMENT_HPP
#define PIXEL_ADVENTURE_GUI_ELEMENT_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>


class GUI_Element
{
public:
    GUI_Element();
    virtual ~GUI_Element() = default;

    virtual void set_parent(GUI_Element* parent);

    virtual void handle_event(const sf::Event& event) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual void select();
    virtual void deselect();
    bool selected() const;
    virtual bool selectable() = 0;

    virtual void activate() = 0;

    virtual sf::FloatRect local_bb() const = 0;
    virtual sf::FloatRect global_bb() const = 0;
    virtual sf::Transform transform() const = 0;
    sf::Transform global_transform() const;

private:
    GUI_Element* m_parent;
    bool m_selected;
};


#endif //PIXEL_ADVENTURE_GUI_ELEMENT_HPP
