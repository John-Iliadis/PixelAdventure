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

void GUI_Sprite::set_pos(float x, float y)
{
    m_transform.setPosition(x, y);
}

void GUI_Sprite::set_scale(float scale)
{
    m_transform.setScale(scale, scale);
}

void GUI_Sprite::set_origin(float x, float y)
{
    m_transform.setOrigin(x, y);
}

void GUI_Sprite::handle_event(const sf::Event &event)
{
}

void GUI_Sprite::draw(sf::RenderWindow &window)
{
    sf::RenderStates render_states;

    render_states.transform = global_transform();
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

sf::FloatRect GUI_Sprite::local_bb()
{
    return
    {
        sf::Vector2f(0, 0),
        static_cast<sf::Vector2f>(m_texture->getSize())
    };
}

sf::FloatRect GUI_Sprite::global_bb()
{
    return global_transform().transformRect(local_bb());
}

sf::Transform GUI_Sprite::transform()
{
    return m_transform.getTransform();
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
