//
// Created by Gianni on 16/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_CONTAINER_HPP
#define PIXEL_ADVENTURE_GUI_CONTAINER_HPP

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include "../world/cursor.hpp"
#include "gui_element.hpp"
#include "gui_sprite.hpp"


class GUI_Container : public GUI_Element
{
public:
    GUI_Container() = default;
    GUI_Container(const sf::Texture& texture);
    ~GUI_Container();

    void pack(GUI_Element* gui_element);

    void set_texture(const sf::Texture& texture);
    void set_pos(float x, float y);
    void set_scale(float scale);
    void set_origin(float x, float y);

    void handle_event(const sf::Event &event) override;
    void draw(sf::RenderWindow &window) override;

    void activate() override;

    bool selectable() override;

    sf::FloatRect local_bb() const override;
    sf::FloatRect global_bb() const override;
    sf::Transform transform() const override;

private:
    GUI_Sprite m_sprite;
    std::vector<GUI_Element*> m_elements;
};


#endif //PIXEL_ADVENTURE_GUI_CONTAINER_HPP
