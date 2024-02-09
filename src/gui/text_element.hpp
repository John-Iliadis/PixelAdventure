//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_TEXT_ELEMENT_HPP
#define PLATFORMER_TEXT_ELEMENT_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "gui_element.hpp"


class TextElement : public GUI_Element
{
public:
    TextElement(const sf::Text& text);

    bool is_selectable() const override;

    void activate() override;

    void update(const sf::Vector2i& mouse_pos) override;
    void handle_event(const sf::Event &event) override;

    sf::Rect<float> get_clickable_area() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Text m_text;
};


#endif //PLATFORMER_TEXT_ELEMENT_HPP
