//
// Created by Gianni on 8/02/2024.
//

#ifndef PLATFORMER_PAPER_LABEL_HPP
#define PLATFORMER_PAPER_LABEL_HPP

#include <cstdint>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../utilities/utils.hpp"
#include "../enums/origin.hpp"
#include "gui_element.hpp"


class PaperLabel final : public GUI_Element
{
public:
    PaperLabel() = default;

    void set_label_texture(const sf::Texture& texture);
    void set_label_position(const sf::Vector2f& pos);
    void set_label_position(float x, float y);
    void set_label_scale(const sf::Vector2f& scale);
    void set_label_scale(float x_factor, float y_factor);
    void set_label_origin(Origin origin);

    void set_text_font(const sf::Font& font);
    void set_text_string(const std::string& string);
    void set_text_character_size(uint32_t size);
    void set_text_color(const sf::Color& color);
    void set_text_offset(const sf::Vector2f& offset);
    void set_text_offset(float x, float y);

    bool is_selectable() const override;

    void activate() override;

    void handle_event(const sf::Event &event) override;

    sf::Rect<float> get_clickable_area() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite m_paper_label;
    mutable sf::Text m_text;
    sf::Vector2f m_offset;
};


#endif //PLATFORMER_PAPER_LABEL_HPP
