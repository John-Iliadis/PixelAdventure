//
// Created by Gianni on 16/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_BUTTON_HPP
#define PIXEL_ADVENTURE_GUI_BUTTON_HPP

#include <functional>
#include <SFML/Graphics/Texture.hpp>
#include "gui_element.hpp"
#include "gui_sprite.hpp"
#include "gui_text.hpp"


class GUI_Button : public GUI_Element
{
public:
    GUI_Button();
    GUI_Button(const sf::Texture& texture, const sf::Font& font, uint32_t char_size, sf::String string = "");

    void set_texture(const sf::Texture& texture);
    void set_font(const sf::Font& font);
    void set_char_size(uint32_t size);
    void set_string(const sf::String& string);
    void set_text_color(const sf::Color& color);
    void set_pos_rel(float x, float y);
    void set_pos_glob(float x, float y);
    void set_scale(float scale);
    void set_text_scale(float scale);
    void set_text_offset(float x, float y);
    void set_origin(Origin origin);
    void set_callback(std::function<void()> callback);
    void set_parent(GUI_Element *parent) override;

    void handle_event(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderWindow &window) override;

    bool selectable() override;
    void activate() override;

    sf::FloatRect bounding_box() const override;

private:
    void set_text_pos();

private:
    GUI_Sprite m_sprite;
    GUI_Text m_text;
    std::function<void()> m_callback;
    sf::Vector2f m_text_offset;
};


#endif //PIXEL_ADVENTURE_GUI_BUTTON_HPP
