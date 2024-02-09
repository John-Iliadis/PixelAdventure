//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_GUI_CONTAINER_HPP
#define PLATFORMER_GUI_CONTAINER_HPP


#include <functional>
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "gui_element.hpp"
#include "../enums/origin.hpp"
#include "../utilities/utils.hpp"


class GUI_Container : public GUI_Element
{
public:
    GUI_Container() = default;

    void push_back(std::unique_ptr<GUI_Element>&& gui_component);

    void set_container_texture(const sf::Texture& texture);
    void set_container_position(const sf::Vector2f& pos);
    void set_container_position(float x, float y);
    void set_container_scale(const sf::Vector2f& scale);
    void set_container_scale(float x, float y);
    void set_container_origin(Origin origin);

    void activate() override;

    void update(const sf::Vector2i& mouse_pos) override;
    void handle_event(const sf::Event &event) override;

    sf::Rect<float> get_clickable_area() const override;
    bool is_selectable() const override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_container;
    std::vector<std::unique_ptr<GUI_Element>> m_gui_components;
};


#endif //PLATFORMER_GUI_CONTAINER_HPP
