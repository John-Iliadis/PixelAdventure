//
// Created by Gianni on 29/01/2024.
//

#include "camera.hpp"


Camera::Camera(uint32_t width, uint32_t height)
    : m_view({0, 0, static_cast<float>(width), static_cast<float>(height)})
    , m_size(width, height)
    , m_current_state(new Camera::IdleState())
{
}

void Camera::update(double dt)
{
    std::unique_ptr<Camera::State> new_state = m_current_state->update(*this, dt);

    if (new_state)
    {
        m_current_state = std::move(new_state);
    }
}

void Camera::set_target(const sf::Vector2f &target, float delay_time, std::function<void()> callback)
{
    m_current_state = std::make_unique<Camera::TargetTransitionState>(*this, target, delay_time, callback);
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
    m_view.setCenter(x, y);
}

void Camera::set_center(const sf::Vector2f& center)
{
    m_view.setCenter(center);
}

sf::Vector2f Camera::get_center() const
{
    return m_view.getCenter();
}

sf::Vector2f Camera::get_size() const
{
    return m_view.getSize();
}

const sf::View &Camera::get_view() const
{
    return m_view;
}

Camera::TargetTransitionState::TargetTransitionState(Camera &camera, const sf::Vector2f &target_pos, float delay_time, std::function<void()> callback)
    : m_callback(std::move(callback))
    , m_start_pos(camera.get_center())
    , m_target_pos(target_pos)
    , m_delay_time(delay_time)
    , m_total_ellapsed()
{
    m_duration = utils::get_distance(m_start_pos, m_target_pos) / 300;
    m_duration = std::clamp(m_duration, 0.5f, 2.f);
}

std::unique_ptr<Camera::State>  Camera::TargetTransitionState::update(Camera &camera, double dt)
{
    if (m_delay_time > 0)
    {
        m_delay_time -= dt;
        return nullptr;
    }

    m_total_ellapsed += dt;

    float t = m_total_ellapsed / m_duration;

    if (t > 1.f) t = 1.f;

    float easing = 1 - std::pow(1 - t, 5);

    sf::Vector2f new_pos = m_start_pos + (m_target_pos - m_start_pos) * easing;

    camera.set_center(new_pos);

    if (new_pos == m_target_pos)
    {
        m_callback? m_callback() : (void)0;
        return std::make_unique<Camera::IdleState>();
    }

    return nullptr;
}
