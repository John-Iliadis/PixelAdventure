//
// Created by Gianni on 6/02/2024.
//

#ifndef PLATFORMER_TEXT_BUTTON_HPP
#define PLATFORMER_TEXT_BUTTON_HPP

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include "../utilities/utils.hpp"
#include "gui_button_base.hpp"


class TextButton final : public GUI_Button_Base
{
public:
    TextButton();

    void set_text_font(const sf::Font& font);
    void set_text_string(const std::string& string);
    void set_text_character_size(uint32_t size);
    void set_text_character_size_hover(uint32_t size);
    void set_text_color(const sf::Color& color);

    void select() override;
    void deselect() override;

    void handle_event(const sf::Event& event) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    mutable sf::Text m_text;
    uint32_t m_character_size;
    uint32_t m_character_size_hover;
};


#endif //PLATFORMER_TEXT_BUTTON_HPP
