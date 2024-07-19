//
// Created by Gianni on 16/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_SPRITE_HPP
#define PIXEL_ADVENTURE_GUI_SPRITE_HPP

#include <cassert>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "../enums/origin.hpp"
#include "gui_element.hpp"


class GUI_Sprite : public GUI_Element
{
public:
    GUI_Sprite();
    GUI_Sprite(const sf::Texture& texture);

    void set_texture(const sf::Texture& texture);
    void set_pos_rel(float x, float y);
    void set_pos_glob(float x, float y);
    void set_scale(float scale);
    void set_origin(Origin origin);

    void handle_event(const sf::Event &event) override;
    void draw(sf::RenderWindow &window) override;

    void activate() override;

    bool selectable() override;
    sf::FloatRect bounding_box() const override;

private:
    void make_vertices();

private:
    sf::Vertex m_vertices[4];
    sf::Transformable m_transform;
    const sf::Texture* m_texture;
};


#endif //PIXEL_ADVENTURE_GUI_SPRITE_HPP
