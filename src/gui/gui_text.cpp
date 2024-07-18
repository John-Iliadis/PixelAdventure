//
// Created by Gianni on 16/07/2024.
//

#include "gui_text.hpp"


GUI_Text::GUI_Text()
    : m_font()
    , m_color(sf::Color::White)
    , m_char_size()
    , m_update()
{
}

GUI_Text::GUI_Text(const sf::Font &font, uint32_t char_size, sf::String string)
    : m_font(&font)
    , m_string(string)
    , m_color(sf::Color::White)
    , m_char_size(char_size)
    , m_update(true)
{
    make_vertices();
}

void GUI_Text::set_font(const sf::Font &font)
{
    m_font = &font;
    m_update = true;
}

void GUI_Text::set_char_size(uint32_t size)
{
    m_char_size = size;
    m_update = true;
}

void GUI_Text::set_string(const sf::String &string)
{
    m_string = string;
    m_update = true;
}

void GUI_Text::set_color(const sf::Color &color)
{
    m_color = color;
    m_update = true;
}

void GUI_Text::set_pos(float x, float y)
{
    m_transform.setPosition(x, y);
}

void GUI_Text::set_scale(float scale)
{
    m_transform.setScale(scale, scale);
}

void GUI_Text::set_origin(float x, float y)
{
    m_transform.setOrigin(x, y);
}

void GUI_Text::handle_event(const sf::Event &event)
{
}

void GUI_Text::draw(sf::RenderWindow &window)
{
    make_vertices();

    sf::RenderStates states;
    states.transform = global_transform();
    states.texture = &m_font->getTexture(m_char_size);

    window.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::Triangles, states);
}

bool GUI_Text::selectable()
{
    return false;
}

void GUI_Text::activate()
{
}

sf::FloatRect GUI_Text::local_bb() const
{
    return m_local_bb;
}

sf::FloatRect GUI_Text::global_bb() const
{
    return transform().transformRect(m_local_bb);
}

sf::Transform GUI_Text::transform() const
{
    return m_transform.getTransform();
}

void GUI_Text::make_vertices()
{
    if (!m_update)
        return;

    m_update = false;

    if (m_string.isEmpty())
        return;

    m_vertices.clear();
    m_local_bb = {};

    float white_space_width = m_font->getGlyph(U' ', m_char_size, false).advance;
    float max_x = 0.f;
    float max_y = 0.f;
    float x = 0.f;
    float y = m_font->getGlyph(U'H', m_char_size, false).bounds.height;
    uint32_t prev_char{};

    for (uint32_t c: m_string)
    {
        x += m_font->getKerning(prev_char, c, m_char_size);

        prev_char = c;

        if (c == U' ')
        {
            x += white_space_width;

            max_x = std::max(max_x, x);
            max_y = std::max(max_y, y);

            continue;
        }

        const sf::Glyph& glyph = m_font->getGlyph(c, m_char_size, false);

        add_glyph_quad({x, y}, glyph);

        sf::Vector2f size = glyph.bounds.getPosition() + glyph.bounds.getSize();

        max_x = std::max(max_x, x + size.x);
        max_y = std::max(max_y, y + size.y);

        x += glyph.advance;
    }

    m_local_bb = {0, 0, max_x, max_y};
}

void GUI_Text::add_glyph_quad(const sf::Vector2f &pos, const sf::Glyph &glyph)
{
    const sf::Vector2f padding(1.f, 1.f);

    sf::Vector2f p1 = glyph.bounds.getPosition() - padding;
    sf::Vector2f p2 = glyph.bounds.getPosition() + glyph.bounds.getSize() + padding;
    sf::Vector2f uv1 = sf::Vector2f(glyph.textureRect.getPosition()) - padding;
    sf::Vector2f uv2 = sf::Vector2f(glyph.textureRect.getPosition() + glyph.textureRect.getSize()) + padding;

    m_vertices.emplace_back(pos + sf::Vector2f(p1.x, p1.y), m_color, sf::Vector2f(uv1.x, uv1.y));
    m_vertices.emplace_back(pos + sf::Vector2f(p2.x, p1.y), m_color, sf::Vector2f(uv2.x, uv1.y));
    m_vertices.emplace_back(pos + sf::Vector2f(p1.x, p2.y), m_color, sf::Vector2f(uv1.x, uv2.y));
    m_vertices.emplace_back(pos + sf::Vector2f(p1.x, p2.y), m_color, sf::Vector2f(uv1.x, uv2.y));
    m_vertices.emplace_back(pos + sf::Vector2f(p2.x, p1.y), m_color, sf::Vector2f(uv2.x, uv1.y));
    m_vertices.emplace_back(pos + sf::Vector2f(p2.x, p2.y), m_color, sf::Vector2f(uv2.x, uv2.y));
}
