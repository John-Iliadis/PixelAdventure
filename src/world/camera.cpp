//
// Created by Gianni on 29/01/2024.
//

#include "camera.hpp"

#include <iostream>

Camera::Camera(sf::RenderWindow* window, uint32_t width, uint32_t height)
    : m_window(window)
    , m_camera({0, 0, static_cast<float>(width), static_cast<float>(height)})
    , m_size(width, height)
    , m_current_state(new IdleState())
{
}

Camera::~Camera()
{
    delete m_current_state;
}

void Camera::resize(float aspect_ratio)
{
    m_camera.setSize(static_cast<int>(m_size.y * aspect_ratio), int(m_size.y));
}

void Camera::update(double dt)
{
    State* new_state = m_current_state->update(*this, dt);

    if (new_state)
    {
        delete m_current_state;
        m_current_state = new_state;
    }

    m_window->setView(m_camera);
}

void Camera::set_target(const sf::Vector2f &target, std::function<void()> callback)
{
    delete m_current_state;

    m_current_state = new TargetTransitionState(*this, target, callback);
}

void Camera::set_size(uint32_t width, uint32_t height)
{
    m_size = {width, height};
}

void Camera::set_size(const sf::Vector2u& size)
{
    m_size = size;
}

void Camera::set_center(float x, float y)
{
    m_camera.setCenter(x, y);
}

void Camera::set_center(const sf::Vector2f& center)
{
    m_camera.setCenter(center);
}

sf::Vector2f Camera::get_center() const
{
    return m_camera.getCenter();
}

Camera::TargetTransitionState::TargetTransitionState(Camera &camera, const sf::Vector2f &target_pos, std::function<void()> callback)
    : m_callback(std::move(callback))
    , m_start_pos(camera.get_center())
    , m_target_pos(target_pos)
    , m_duration(2)
    , m_total_ellapsed()
{
}

Camera::State* Camera::TargetTransitionState::update(Camera &camera, double dt)
{
    m_total_ellapsed += dt;

    float t = m_total_ellapsed / m_duration;

    if (t > 1.f) t = 1.f;

    float easing = 1 - std::pow(1 - t, 5);

    sf::Vector2f new_pos = m_start_pos + (m_target_pos - m_start_pos) * easing;

    camera.set_center(new_pos);

    if (new_pos == m_target_pos)
    {
        m_callback? m_callback() : (void)0;
        return new IdleState();
    }

    return nullptr;
}
