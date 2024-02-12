//
// Created by Gianni on 9/02/2024.
//

#ifndef PLATFORMER_GUI_BUILDER_HPP
#define PLATFORMER_GUI_BUILDER_HPP

#include <functional>
#include <memory>
#include "../asset_managers/texture_manager.hpp"
#include "../asset_managers/font_manager.hpp"
#include "../utilities/utils.hpp"
#include "button.hpp"
#include "text_button.hpp"
#include "gui_container.hpp"
#include "slider.hpp"
#include "text_element.hpp"
#include "sprite_element.hpp"


class GUI_Builder
{
public:
    GUI_Builder();
    GUI_Builder(const TextureManager* textures, const FontManager* fonts);

    GUI_Builder& set_texture(const std::string& texture_id);
    GUI_Builder& set_position(const sf::Vector2f& pos);
    GUI_Builder& set_position(float x, float y);
    GUI_Builder& set_scale(const sf::Vector2f& scale);
    GUI_Builder& set_scale(float x_factor, float y_factor);
    GUI_Builder& set_scale_hover(const sf::Vector2f& scale);
    GUI_Builder& set_scale_hover(float x_factor, float y_factor);
    GUI_Builder& set_origin(Origin origin);
    GUI_Builder& set_color(const sf::Color& color);
    GUI_Builder& set_text_color(const sf::Color& color);
    GUI_Builder& set_callback(std::function<void()> callback);
    GUI_Builder& set_font(const std::string& font_id);
    GUI_Builder& set_text_string(const std::string& string);
    GUI_Builder& set_character_size(uint32_t character_size);
    GUI_Builder& set_character_size_hover(uint32_t character_size_hover);
    GUI_Builder& set_text_offset(const sf::Vector2f& offset);
    GUI_Builder& set_text_offset(float offset_x, float offset_y);
    GUI_Builder& set_slider_value(float* slider_value);
    GUI_Builder& set_slider_min(float min);
    GUI_Builder& set_slider_max(float max);

    std::unique_ptr<Button> make_button();
    std::unique_ptr<TextButton> make_text_button();
    std::unique_ptr<Slider> make_slider();
    std::unique_ptr<TextElement> make_text_element();
    std::unique_ptr<SpriteElement> make_sprite_element();

    void reset();

private:
    const TextureManager* m_textures;
    const FontManager* m_fonts;

    sf::Vector2f m_position;
    sf::Vector2f m_scale;
    sf::Vector2f m_hover_scale;
    Origin m_origin;
    std::function<void()> m_callback;
    std::string m_texture_id;
    std::string m_font_id;
    std::string m_text_string;
    uint32_t m_character_size;
    uint32_t m_character_size_hover;
    sf::Vector2f m_text_offset;
    sf::Color m_color;
    sf::Color m_text_color;
    float* m_slider_value;
    float m_min;
    float m_max;
};


#endif //PLATFORMER_GUI_BUILDER_HPP
