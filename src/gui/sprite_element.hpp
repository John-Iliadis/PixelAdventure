//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_SPRITE_ELEMENT_HPP
#define PLATFORMER_SPRITE_ELEMENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "gui_element.hpp"


class SpriteElement : public GUI_Element
{
public:
    SpriteElement(const sf::Sprite& sprite);

    bool is_selectable() const override;

    void activate() override;

    void update() override;
    void handle_event(const sf::Event &event) override;

    sf::Rect<float> get_clickable_area() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
};


#endif //PLATFORMER_SPRITE_ELEMENT_HPP
