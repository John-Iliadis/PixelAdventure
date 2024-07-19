//
// Created by Gianni on 16/07/2024.
//

#include "gui_sprite.hpp"


GUI_Sprite::GUI_Sprite()
    : m_texture()
{
}

GUI_Sprite::GUI_Sprite(const sf::Texture &texture)
    : m_texture(&texture)
{
    make_vertices();
}

void GUI_Sprite::set_texture(const sf::Texture &texture)
{
    m_texture = &texture;
    make_vertices();
}

void GUI_Sprite::set_pos_rel(float x, float y)
{
    sf::Vector2f parent_pos = m_parent? m_parent->bounding_box().getPosition() : sf::Vector2f();

    m_transform.setPosition(parent_pos.x + x, parent_pos.y + y);
}

void GUI_Sprite::set_pos_glob(float x, float y)
{
    m_transform.setPosition(x, y);
}

void GUI_Sprite::set_scale(float scale)
{
    m_transform.setScale(scale, scale);
}

void GUI_Sprite::set_origin(Origin origin)
{
    const auto [width, height] = sf::Vector2f(m_texture->getSize());

    switch (origin)
    {
        case Origin::TOP_LEFT:
            m_transform.setOrigin(0.f, 0.f);
            break;

        case Origin::CENTER:
            m_transform.setOrigin(width / 2.f, height / 2.f);
            break;

        case Origin::CENTER_BOTTOM:
            m_transform.setOrigin(width / 2.f, height);
            break;

        case Origin::CENTER_TOP:
            m_transform.setOrigin(width / 2.f, 0.f);
            break;

        case Origin::CENTER_LEFT:
            m_transform.setOrigin(0.f, height / 2.f);
            break;

        case Origin::CENTER_RIGHT:
            m_transform.setOrigin(0.f, height / 2.f);
            break;
    }
}

void GUI_Sprite::handle_event(const sf::Event &event)
{
}

void GUI_Sprite::draw(sf::RenderWindow &window)
{
    sf::RenderStates render_states;

    render_states.transform = m_transform.getTransform();
    render_states.texture = m_texture;

    window.draw(m_vertices, 4, sf::PrimitiveType::TriangleStrip, render_states);
}

bool GUI_Sprite::selectable()
{
    return false;
}

void GUI_Sprite::activate()
{
}

sf::FloatRect GUI_Sprite::bounding_box() const
{
    sf::FloatRect local_bounding_box
    {
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(m_texture->getSize())
    };

    return m_transform.getTransform().transformRect(local_bounding_box);
}

void GUI_Sprite::make_vertices()
{
    assert(m_texture);

    sf::Vector2f tex_size = static_cast<sf::Vector2f>(m_texture->getSize());

    m_vertices[0].texCoords = {0.f, 0.f};
    m_vertices[1].texCoords = {0.f, tex_size.y};
    m_vertices[2].texCoords = {tex_size.x, 0.f};
    m_vertices[3].texCoords = tex_size;

    m_vertices[0].position = m_vertices[0].texCoords;
    m_vertices[1].position = m_vertices[1].texCoords;
    m_vertices[2].position = m_vertices[2].texCoords;
    m_vertices[3].position = m_vertices[3].texCoords;
}
