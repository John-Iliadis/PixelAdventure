//
// Created by Gianni on 22/01/2024.
//

#ifndef PLATFORMER_SPRITE_COLLIDER_HPP
#define PLATFORMER_SPRITE_COLLIDER_HPP

#include <array>
#include <cmath>
#include <cassert>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums.hpp"


class SpriteCollider : public sf::Drawable
{
public:
    SpriteCollider();
    virtual ~SpriteCollider() = default;

    void set_texture(const sf::Texture& texture, bool reset_rect = true);
    void set_texture_rect(const sf::IntRect& rect);
    void set_position(const sf::Vector2f& pos);
    void set_position(float x, float y);
    void set_scale(const sf::Vector2f& scale);
    void set_scale(float x, float y);
    void set_rotation(float degrees);
    void set_origin(Origin origin);
    void set_sprite_origin(Origin origin);
    void set_collider_origin(Origin origin);
    void set_collider_size(float width, float height);
    void set_collider_size(const sf::Vector2f& size);

    void move(const sf::Vector2f& offset);
    void move(float x, float y);
    void scale(const sf::Vector2f& scale);
    void scale(float x, float y);
    void rotate(float degrees);

    sf::FloatRect get_sprite_rect() const;
    sf::FloatRect get_collider() const;
    const sf::Vector2f& get_position() const;
    const sf::Vector2f& get_scale() const;
    float get_rotation() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update_positions();
    void update_texture_coords();

    sf::Transform get_transform(const sf::Vector2f& origin) const;

private:
    std::array<sf::Vertex, 4> m_sprite_vertices;
    const sf::Texture* m_texture_ptr;

    sf::IntRect m_texture_rect;
    sf::FloatRect m_collider_rect;

    sf::Vector2f m_sprite_origin;
    sf::Vector2f m_collider_origin;

    sf::Vector2f m_position;
    sf::Vector2f m_scale;
    float m_rotation;
};

#endif //PLATFORMER_SPRITE_COLLIDER_HPP
