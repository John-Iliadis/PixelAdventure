//
// Created by Gianni on 29/01/2024.
//

#include "camera.hpp"


Camera::Camera(sf::RenderWindow* window, uint32_t width, uint32_t height)
    : m_window(window)
    , m_camera({0, 0, static_cast<float>(width), static_cast<float>(height)})
    , m_size(width, height)
    , m_current_state(new Camera::IdleState())
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

    set_current_view();
}

void Camera::set_target(const sf::Vector2f &target, float delay_time, std::function<void()> callback)
{
    delete m_current_state;

    m_current_state = new Camera::TargetTransitionState(*this, target, delay_time, callback);
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

Camera &Camera::operator=(Camera &&other) noexcept
{
    if (this != &other)
    {
        m_window = other.m_window;
        m_camera = other.m_camera;
        m_size = other.m_size;
        m_current_state = other.m_current_state;

        other.m_window = nullptr;
        other.m_current_state = nullptr;
    }

    return *this;
}

sf::Vector2f Camera::get_size() const
{
    return m_camera.getSize();
}

void Camera::set_current_view()
{
    m_window->setView(m_camera);
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

Camera::State* Camera::TargetTransitionState::update(Camera &camera, double dt)
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
        return new Camera::IdleState();
    }

    return nullptr;
}
