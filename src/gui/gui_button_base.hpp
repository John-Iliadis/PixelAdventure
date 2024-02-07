//
// Created by Gianni on 6/02/2024.
//

#ifndef PLATFORMER_GUI_BUTTON_BASE_HPP
#define PLATFORMER_GUI_BUTTON_BASE_HPP

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../utilities/utils.hpp"
#include "gui_component.hpp"


class GUI_Button_Base : public GUI_Component
{
public:
    GUI_Button_Base();
    virtual ~GUI_Button_Base() = default;

    void set_position(const sf::Vector2f& pos);
    void set_position(float x, float y);

    void set_button_texture(const sf::Texture& texture);
    void set_button_origin(Origin origin);
    void set_button_scale(const sf::Vector2f& scale);
    void set_button_scale(float factor_x, float factor_y);
    void set_button_hover_scale(const sf::Vector2f& scale);
    void set_button_hover_scale(float x_factor, float y_factor);
    void set_button_callback(std::function<void()> callback);

    bool is_selectable() const override;

    void activate() override;
    void deactivate() override;

    sf::Rect<float> get_clickable_area() const override;

protected:
    sf::Sprite m_button;
    sf::Vector2f m_button_scale;
    sf::Vector2f m_button_hover_scale;

    std::function<void()> m_callback;
};


#endif //PLATFORMER_GUI_BUTTON_BASE_HPP
