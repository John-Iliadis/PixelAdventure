//
// Created by Gianni on 22/01/2024.
//

#include "sprite_collider.hpp"


SpriteCollider::SpriteCollider()
        : m_texture_ptr(nullptr)
        , m_scale(1, 1)
        , m_rotation()
        , m_origin(Origin::TOP_LEFT)
{
}

void SpriteCollider::set_texture(const sf::Texture& texture, bool reset_rect)
{
    m_texture_ptr = &texture;

    reset_rect? set_texture_rect({{0, 0}, {sf::Vector2i(texture.getSize())}}) : (void)0;
}

void SpriteCollider::set_texture_rect(const sf::IntRect &rect)
{
    if (rect == m_texture_rect) return;

    auto previous_size = m_texture_rect.getSize();

    m_texture_rect = rect;
    update_positions();
    update_texture_coords();

    if (m_texture_rect.getSize() != previous_size)
        set_origin(m_origin);
}

void SpriteCollider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform = get_transform(m_sprite_origin);
    states.texture = m_texture_ptr;

    target.draw(m_sprite_vertices.data(), m_sprite_vertices.size(), sf::PrimitiveType::TriangleStrip, states);
}

void SpriteCollider::update_positions()
{
    const float width = static_cast<float>(std::abs(m_texture_rect.width));
    const float height = static_cast<float>(std::abs(m_texture_rect.height));

    m_sprite_vertices[0].position = {0, 0};
    m_sprite_vertices[1].position = {0, height};
    m_sprite_vertices[2].position = {width, 0};
    m_sprite_vertices[3].position = {width, height};
}

void SpriteCollider::update_texture_coords()
{
    const sf::FloatRect rect = static_cast<sf::FloatRect>(m_texture_rect);

    const float top = rect.top;
    const float bottom = top + rect.height;
    const float left = rect.left;
    const float right = left + rect.width;

    m_sprite_vertices[0].texCoords = {left, top};
    m_sprite_vertices[1].texCoords = {left, bottom};
    m_sprite_vertices[2].texCoords = {right, top};
    m_sprite_vertices[3].texCoords = {right, bottom};
}

sf::Transform SpriteCollider::get_transform(const sf::Vector2f &origin) const
{
    const float angle = -m_rotation * M_PI / 180.f;
    const float cos = std::cos(angle);
    const float sin = std::sin(angle);

    const float sxc = m_scale.x * cos;
    const float syc = m_scale.y * cos;
    const float sxs = m_scale.x * sin;
    const float sys = m_scale.y * sin;

    const float tx = -origin.x * sxc - origin.y * sys + m_position.x;
    const float ty = origin.x * sxs - origin.y * syc + m_position.y;

    return {
            sxc, sys, tx,
            -sxs, syc, ty,
            0.f, 0.f, 1.f
    };
}

void SpriteCollider::set_position(const sf::Vector2f &pos)
{
    m_position = pos;
}

void SpriteCollider::set_position(float x, float y)
{
    m_position = {x, y};
}

void SpriteCollider::set_scale(const sf::Vector2f &scale)
{
    m_scale = scale;
}

void SpriteCollider::set_scale(float x, float y)
{
    m_scale = {x, y};
}

void SpriteCollider::set_rotation(float degrees)
{
    m_rotation = degrees;
}

void SpriteCollider::set_color(sf::Color color)
{
    for (auto& vertex : m_sprite_vertices)
        vertex.color = color;
}

void SpriteCollider::set_collider_size(float width, float height)
{
    m_collider_rect.width = width;
    m_collider_rect.height = height;
}

void SpriteCollider::set_collider_size(const sf::Vector2f &size)
{
    set_collider_size(size.x, size.y);
}

void SpriteCollider::move(const sf::Vector2f &offset)
{
    set_position(m_position + offset);
}

void SpriteCollider::move(float x, float y)
{
    set_position(m_position + sf::Vector2f(x, y));
}

void SpriteCollider::scale(const sf::Vector2f &scale)
{
    set_scale(m_scale.x * scale.x, m_scale.y * scale.y);
}

void SpriteCollider::scale(float x, float y)
{
    set_scale(m_scale.x * x, m_scale.y * y);
}

void SpriteCollider::rotate(float degrees)
{
    set_rotation(m_rotation + degrees);
}

const sf::Vector2f &SpriteCollider::get_position() const
{
    return m_position;
}

const sf::Vector2f &SpriteCollider::get_scale() const
{
    return m_scale;
}

float SpriteCollider::get_rotation() const
{
    return m_rotation;
}

sf::FloatRect SpriteCollider::get_sprite_rect() const
{
    return get_transform(m_sprite_origin).transformRect(sf::FloatRect(0, 0, m_texture_rect.width, m_texture_rect.height));
}

sf::FloatRect SpriteCollider::get_collider() const
{
    return get_transform(m_collider_origin).transformRect(m_collider_rect);
}

void SpriteCollider::set_origin(Origin origin)
{
    m_origin = origin;

    sf::Vector2f texture_size = static_cast<sf::Vector2f>(m_texture_rect.getSize());
    sf::Vector2f collider_size = m_collider_rect.getSize();

    if (texture_size == sf::Vector2f(0, 0))
        puts("Warning: SpriteCollider::set_origin: Texture size is {0,0}");

    if (collider_size == sf::Vector2f(0, 0))
        puts("Warning: SpriteCollider::set_origin: Collider size is {0, 0}");

    switch (origin)
    {
        case Origin::TOP_LEFT:
        {
            m_sprite_origin = {};
            m_collider_origin = {};

            break;
        }

        case Origin::CENTER:
        {
            m_sprite_origin = texture_size / 2.f;
            m_collider_origin = collider_size / 2.f;

            break;
        }

        case Origin::CENTER_BOTTOM:
        {
            m_sprite_origin = {texture_size.x / 2.f, texture_size.y};
            m_collider_origin = {collider_size.x / 2.f, collider_size.y};

            break;
        }
    }
}
