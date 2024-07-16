//
// Created by Gianni on 16/07/2024.
//

#include "gui_sprite.hpp"


GUI_Sprite::GUI_Sprite()
    : m_vertices()
    , m_texture()
{
}

GUI_Sprite::GUI_Sprite(const sf::Texture &texture)
    : m_vertices()
    , m_texture(&texture)
{
    make_vertices();
}

void GUI_Sprite::set_texture(const sf::Texture &texture)
{
    if (m_texture != &texture)
    {
        m_texture = &texture;
        make_vertices();
    }
}

void GUI_Sprite::handle_event(const sf::Event &event)
{
}

void GUI_Sprite::draw(sf::RenderWindow &window)
{
    sf::RenderStates render_states;

    render_states.transform = getTransform();
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

sf::FloatRect GUI_Sprite::bounding_box()
{
    assert(m_texture);

    return
    {
        sf::Vector2f(0, 0),
        static_cast<sf::Vector2f>(m_texture->getSize())
    };
}

sf::Transform GUI_Sprite::transform()
{
    return getTransform();
}

void GUI_Sprite::make_vertices()
{
    assert(m_texture);

    sf::Vector2f tex_size = static_cast<sf::Vector2f>(m_texture->getSize());

    m_vertices[0].position = {0.f, 0.f};
    m_vertices[1].position = {0.f, tex_size.y};
    m_vertices[2].position = {tex_size.x, 0.f};
    m_vertices[3].position = tex_size;

    m_vertices[0].texCoords = m_vertices[0].position;
    m_vertices[1].texCoords = m_vertices[1].position;
    m_vertices[2].texCoords = m_vertices[2].position;
    m_vertices[3].texCoords = m_vertices[3].position;
}
