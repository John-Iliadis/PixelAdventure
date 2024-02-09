//
// Created by Gianni on 9/02/2024.
//

#include "gui_builder.hpp"


GUI_Builder::GUI_Builder()
    : m_textures(nullptr)
    , m_fonts(nullptr)
    , m_slider_value(nullptr)
{
    reset();
}

GUI_Builder::GUI_Builder(const TextureManager *textures, const FontManager* fonts)
    : m_textures(textures)
    , m_fonts(fonts)
{
    reset();
}

GUI_Builder &GUI_Builder::set_texture(const std::string &texture_id)
{
    m_texture_id = texture_id;
    return *this;
}

GUI_Builder &GUI_Builder::set_position(const sf::Vector2f &pos)
{
    m_position = pos;
    return *this;
}

GUI_Builder &GUI_Builder::set_position(float x, float y)
{
    m_position = {x, y};
    return *this;
}

GUI_Builder &GUI_Builder::set_scale(const sf::Vector2f &scale)
{
    m_scale = scale;
    return *this;
}

GUI_Builder &GUI_Builder::set_scale(float x_factor, float y_factor)
{
    m_scale = {x_factor, y_factor};
    return *this;
}

GUI_Builder &GUI_Builder::set_scale_hover(const sf::Vector2f &scale)
{
    m_hover_scale = scale;
    return *this;
}

GUI_Builder &GUI_Builder::set_scale_hover(float x_factor, float y_factor)
{
    m_hover_scale = {x_factor, y_factor};
    return *this;
}

GUI_Builder &GUI_Builder::set_origin(Origin origin)
{
    m_origin = origin;
    return *this;
}

GUI_Builder &GUI_Builder::set_color(const sf::Color &color)
{
    m_color = color;
    return *this;
}

GUI_Builder &GUI_Builder::set_callback(std::function<void()> callback)
{
    m_callback = std::move(callback);
    return *this;
}

GUI_Builder &GUI_Builder::set_text_color(const sf::Color &color)
{
    m_text_color = color;
    return *this;
}

GUI_Builder &GUI_Builder::set_font(const std::string &font_id)
{
    m_font_id = font_id;
    return *this;
}

GUI_Builder &GUI_Builder::set_text_string(const std::string &string)
{
    m_text_string = string;
    return *this;
}

GUI_Builder &GUI_Builder::set_character_size(uint32_t character_size)
{
    m_character_size = character_size;
    return *this;
}

GUI_Builder &GUI_Builder::set_character_size_hover(uint32_t character_size_hover)
{
    m_character_size_hover = character_size_hover;
    return *this;
}

GUI_Builder &GUI_Builder::set_text_offset(const sf::Vector2f &offset)
{
    m_text_offset = offset;
    return *this;
}

GUI_Builder &GUI_Builder::set_text_offset(float offset_x, float offset_y)
{
    m_text_offset = {offset_x, offset_y};
    return *this;
}

GUI_Builder &GUI_Builder::set_slider_value(float *slider_value)
{
    m_slider_value = slider_value;
    return *this;
}

GUI_Builder &GUI_Builder::set_slider_min(float min)
{
    m_min = min;
    return *this;
}

GUI_Builder &GUI_Builder::set_slider_max(float max)
{
    m_max = max;
    return *this;
}

std::unique_ptr<Button> GUI_Builder::make_button()
{
    assert(!m_texture_id.empty());

    if (!m_callback) puts("GUI_Builder::make_button: callback empty");

    auto button = std::make_unique<Button>();

    button->set_button_texture(m_textures->get(m_texture_id));
    button->set_position(m_position);
    button->set_button_scale(m_scale);
    button->set_button_hover_scale(m_hover_scale);
    button->set_button_origin(m_origin);
    button->set_button_color(m_color);
    button->set_button_callback(m_callback);

    reset();

    return button;
}

std::unique_ptr<TextButton> GUI_Builder::make_text_button()
{
    assert(!m_texture_id.empty());
    assert(!m_font_id.empty());
    assert(!m_text_string.empty());
    assert(m_character_size);
    assert(m_character_size_hover);

    if (!m_callback) puts("GUI_Builder::make_text_button: callback empty");

    auto text_button = std::make_unique<TextButton>();

    text_button->set_button_texture(m_textures->get(m_texture_id));
    text_button->set_position(m_position);
    text_button->set_button_scale(m_scale);
    text_button->set_button_hover_scale(m_hover_scale);
    text_button->set_button_origin(m_origin);
    text_button->set_button_color(m_color);
    text_button->set_button_callback(m_callback);

    text_button->set_text_font(m_fonts->get(m_font_id));
    text_button->set_text_string(m_text_string);
    text_button->set_text_character_size(m_character_size);
    text_button->set_text_character_size_hover(m_character_size_hover);
    text_button->set_text_color(m_text_color);
    text_button->set_text_offset(m_text_offset);

    reset();

    return text_button;
}

std::unique_ptr<GUI_Container> GUI_Builder::make_container()
{
    assert(!m_texture_id.empty());

    auto container = std::make_unique<GUI_Container>();

    container->set_container_texture(m_textures->get(m_texture_id));
    container->set_container_position(m_position);
    container->set_container_scale(m_scale);
    container->set_container_origin(m_origin);

    reset();

    return container;
}

std::unique_ptr<Slider> GUI_Builder::make_slider()
{
    assert(m_textures);
    assert(m_slider_value);

    auto slider = std::make_unique<Slider>(*m_textures, m_slider_value, m_min, m_max);

    slider->set_slider_position(m_position);
    slider->set_slider_scale(m_scale);
    slider->set_slider_origin(m_origin);

    reset();

    return slider;
}

std::unique_ptr<TextElement> GUI_Builder::make_text_element()
{
    assert(!m_text_string.empty());
    assert(m_character_size);

    sf::Text text;

    text.setFont(m_fonts->get(m_font_id));
    text.setString(m_text_string);
    text.setCharacterSize(m_character_size);
    text.setFillColor(m_text_color);
    text.setPosition(m_position);

    utils::set_origin(text, m_origin);

    reset();

    return std::make_unique<TextElement>(text);
}

std::unique_ptr<SpriteElement> GUI_Builder::make_sprite_element()
{
    sf::Sprite sprite;

    sprite.setTexture(m_textures->get(m_texture_id));
    sprite.setPosition(m_position);
    sprite.setScale(m_scale);
    sprite.setColor(m_color);

    utils::set_origin(sprite, m_origin);

    reset();

    return std::make_unique<SpriteElement>(sprite);
}

void GUI_Builder::reset()
{
    m_position = {};
    m_scale = {1, 1};
    m_hover_scale = {1, 1};
    m_origin = Origin::TOP_LEFT;
    m_callback = nullptr;
    m_texture_id = {};
    m_font_id = {};
    m_text_string = {};
    m_character_size = {};
    m_character_size_hover = {};
    m_text_offset = {};
    m_color = sf::Color::White;
    m_text_color = sf::Color::White;
    m_slider_value = nullptr;
    m_min = {};
    m_max = {};
}
