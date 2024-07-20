//
// Created by Gianni on 16/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_CONTAINER_HPP
#define PIXEL_ADVENTURE_GUI_CONTAINER_HPP

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include "cursor.hpp"
#include "../enums/origin.hpp"
#include "cursor.hpp"
#include "gui_sprite.hpp"
#include "gui_element.hpp"


class GUI_Container : public GUI_Element
{
public:
    GUI_Container() = default;
    GUI_Container(const sf::Texture& texture);
    ~GUI_Container();

    void pack(GUI_Element* gui_element);

    void set_texture(const sf::Texture& texture);
    void set_pos_rel(float x, float y);
    void set_pos_glob(float x, float y);
    void set_scale(float scale);
    void set_origin(Origin origin);
    void set_parent(GUI_Element *parent) override;

    void handle_event(const sf::Event &event) override;
    void draw(sf::RenderWindow &window) override;

    void activate() override;

    bool selectable() override;
    sf::FloatRect bounding_box() const override;

private:
    GUI_Sprite m_sprite;
    std::vector<GUI_Element*> m_elements;
};


#endif //PIXEL_ADVENTURE_GUI_CONTAINER_HPP
