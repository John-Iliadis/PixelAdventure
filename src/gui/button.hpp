//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_BUTTON_HPP
#define PLATFORMER_BUTTON_HPP

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../utilities/utils.hpp"
#include "gui_element.hpp"


class Button : public GUI_Element
{
public:
    Button();
    virtual ~Button() = default;

    void set_button_texture(const sf::Texture& texture);
    void set_position(const sf::Vector2f& pos);
    void set_position(float x, float y);
    void set_button_origin(Origin origin);
    void set_button_scale(const sf::Vector2f& scale);
    void set_button_scale(float factor_x, float factor_y);
    void set_button_hover_scale(const sf::Vector2f& scale);
    void set_button_hover_scale(float x_factor, float y_factor);
    void set_button_color(const sf::Color& color);
    void set_button_callback(std::function<void()> callback);

    void select() override;
    void deselect() override;

    void update(const sf::Vector2i& mouse_pos) override;
    void handle_event(const sf::Event &event) override;

    void activate() override;

    sf::Rect<float> get_clickable_area() const override;
    bool is_selectable() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    sf::Sprite m_button;
    sf::Vector2f m_button_scale;
    sf::Vector2f m_button_hover_scale;

    std::function<void()> m_callback;
};


#endif //PLATFORMER_BUTTON_HPP
