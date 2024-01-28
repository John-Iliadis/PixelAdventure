//
// Created by Gianni on 28/01/2024.
//

#ifndef PLATFORMER_MOVABLE_OBJECT_HPP
#define PLATFORMER_MOVABLE_OBJECT_HPP

#include <SFML/System/Vector2.hpp>


class MovableObject
{
public:
    MovableObject() = default;
    virtual ~MovableObject() = default;

    void set_velocity(float x, float y);
    void set_velocity(const sf::Vector2f& velocity);
    void set_speed(float x, float y);
    void set_speed(const sf::Vector2f& speed);
    void set_x_velocity(float x);
    void set_y_velocity(float y);
    void set_x_speed(float x);
    void set_y_speed(float y);

    const sf::Vector2f& get_velocity() const;
    const sf::Vector2f& get_speed() const;
    float get_x_velocity() const;
    float get_y_velocity() const;
    float get_x_speed() const;
    float get_y_speed() const;

protected:
    sf::Vector2f m_velocity;
    sf::Vector2f m_speed;
};


#endif //PLATFORMER_MOVABLE_OBJECT_HPP
