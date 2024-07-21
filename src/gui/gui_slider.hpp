//
// Created by Gianni on 16/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_SLIDER_HPP
#define PIXEL_ADVENTURE_GUI_SLIDER_HPP

#include <cassert>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "gui_sprite.hpp"


class GUI_Slider : public GUI_Element
{
public:
    GUI_Slider();
    GUI_Slider(const sf::Texture& slider_tex, const sf::Texture& slider_ptr_tex);
    GUI_Slider(const sf::Texture& slider_tex,
               const sf::Texture& slider_ptr_tex,
               float* value, float min = 0.f, float max = 100.f);

    void set_textures(const sf::Texture& slider_tex, const sf::Texture& slider_ptr_tex);
    void set_value(float* value, float min = 0.f, float max = 100.f);
    void set_pos_rel(float x, float y);
    void set_pos_glob(float x, float y);
    void set_scale(float scale);
    void set_origin(Origin origin);
    void set_parent(GUI_Element *parent) override;

    void handle_event(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderWindow &window) override;

    void activate() override;
    bool selectable() override;

    sf::FloatRect bounding_box() const override;

private:
    void set_slider_ptr();

private:
    GUI_Sprite m_slider;
    GUI_Sprite m_slider_ptr;
    float* m_value;
    float m_min;
    float m_max;
    bool m_dragging;
};


#endif //PIXEL_ADVENTURE_GUI_SLIDER_HPP
