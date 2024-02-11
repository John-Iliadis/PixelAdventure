//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_SLIDER_HPP
#define PLATFORMER_SLIDER_HPP

#include <cassert>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../asset_managers/texture_manager.hpp"
#include "../enums/origin.hpp"
#include "../utilities/utils.hpp"
#include "gui_element.hpp"


class Slider : public GUI_Element
{
public:
    Slider();
    Slider(const TextureManager& textures, float* value, float min = 0, float max = 100);

    void set_slider_position(const sf::Vector2f& pos);
    void set_slider_position(float x, float y);
    void set_slider_scale(const sf::Vector2f& scale);
    void set_slider_scale(float x_factor, float y_factor);
    void set_slider_origin(Origin origin);

    bool is_selectable() const override;

    void activate() override;

    void update() override;
    void handle_event(const sf::Event &event) override;

    sf::Rect<float> get_clickable_area() const override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void set_slider_pointer();

private:
    sf::Sprite m_slider;
    sf::Sprite m_slider_pointer;
    float* m_value;
    float m_min;
    float m_max;
    bool m_dragging;
    bool m_needs_update;
};


#endif //PLATFORMER_SLIDER_HPP
