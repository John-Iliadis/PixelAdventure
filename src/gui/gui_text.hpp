//
// Created by Gianni on 16/07/2024.
//

#ifndef PIXEL_ADVENTURE_GUI_TEXT_HPP
#define PIXEL_ADVENTURE_GUI_TEXT_HPP

#include <vector>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "../enums/origin.hpp"
#include "gui_element.hpp"


class GUI_Text : public GUI_Element
{
public:
    GUI_Text();
    GUI_Text(const sf::Font& font, uint32_t char_size, sf::String string = "");

    void set_font(const sf::Font& font);
    void set_char_size(uint32_t size);
    void set_string(const sf::String& string);
    void set_color(const sf::Color& color);

    void set_pos_rel(float x, float y);
    void set_pos_glob(float x, float y);
    void set_scale(float scale);
    void set_origin(Origin origin);

    void handle_event(const sf::Event &event) override;
    void update() override;
    void draw(sf::RenderWindow &window) override;

    void activate() override;

    bool selectable() override;
    sf::FloatRect bounding_box() const override;

private:
    void make_vertices() const;
    void add_glyph_quad(const sf::Vector2f& pos, const sf::Glyph& glyph) const;

private:
    mutable std::vector<sf::Vertex> m_vertices;
    const sf::Font* m_font;
    sf::Transformable m_transform;
    sf::String m_string;
    sf::Color m_color;
    uint32_t m_char_size;
    mutable sf::FloatRect m_local_bb;
    mutable bool m_update;
};


#endif //PIXEL_ADVENTURE_GUI_TEXT_HPP
