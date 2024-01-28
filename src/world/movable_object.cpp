//
// Created by Gianni on 28/01/2024.
//

#include "movable_object.hpp"


void MovableObject::set_velocity(float x, float y)
{
    m_velocity = {x, y};
}

void MovableObject::set_velocity(const sf::Vector2f &velocity)
{
    m_velocity = velocity;
}

void MovableObject::set_speed(float x, float y)
{
    m_speed = {x, y};
}

void MovableObject::set_speed(const sf::Vector2f &speed)
{
    m_speed = speed;
}

void MovableObject::set_x_velocity(float x)
{
    m_velocity.x = x;
}

void MovableObject::set_y_velocity(float y)
{
    m_velocity.y = y;
}

void MovableObject::set_x_speed(float x)
{
    m_speed.x = x;
}

void MovableObject::set_y_speed(float y)
{
    m_speed.y = y;
}

const sf::Vector2f &MovableObject::get_velocity() const
{
    return m_velocity;
}

const sf::Vector2f &MovableObject::get_speed() const
{
    return m_speed;
}

float MovableObject::get_x_velocity() const
{
    return m_velocity.x;
}

float MovableObject::get_y_velocity() const
{
    return m_velocity.y;
}

float MovableObject::get_x_speed() const
{
    return m_speed.x;
}

float MovableObject::get_y_speed() const
{
    return m_speed.y;
}
