//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_TEXT_BUTTON_HPP
#define PLATFORMER_TEXT_BUTTON_HPP

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include "../utilities/utils.hpp"
#include "button.hpp"


class TextButton final : public Button
{
public:
    TextButton();

    void set_text_font(const sf::Font& font);
    void set_text_string(const std::string& string);
    void set_text_character_size(uint32_t size);
    void set_text_character_size_hover(uint32_t size);
    void set_text_color(const sf::Color& color);
    void set_text_offset(const sf::Vector2f& offset);
    void set_text_offset(float x, float y);

    void select() override;
    void deselect() override;

    void update() override;
    void handle_event(const sf::Event& event) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Text m_text;
    uint32_t m_character_size;
    uint32_t m_character_size_hover;
    sf::Vector2f m_offset;
};


#endif //PLATFORMER_TEXT_BUTTON_HPP
