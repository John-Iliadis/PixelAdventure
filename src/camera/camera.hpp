//
// Created by Gianni on 29/01/2024.
//

#ifndef PLATFORMER_CAMERA_HPP
#define PLATFORMER_CAMERA_HPP

#include <cstdint>
#include <functional>
#include <cmath>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include "../utilities/utils.hpp"


class Camera : sf::NonCopyable
{
public:
    Camera() = default;
    Camera(sf::RenderWindow* window, uint32_t width, uint32_t height);
    ~Camera();

    void update(double dt);

    void set_target(const sf::Vector2f& target, float delay_time = 0, std::function<void()> callback = nullptr);

    void set_size(uint32_t width, uint32_t height);
    void set_size(const sf::Vector2u& size);
    void set_center(float x, float y);
    void set_center(const sf::Vector2f& center);
    void set_current_view();

    sf::Vector2f get_center() const;
    sf::Vector2f get_size() const;

    Camera(Camera&&) noexcept = delete;
    Camera& operator=(Camera&& other) noexcept;

private:
    class State
    {
    public:
        virtual ~State() = default;
        virtual State* update(Camera& camera, double dt) { return nullptr; };
    };

    class TargetTransitionState : public State
    {
    public:
        TargetTransitionState(Camera& camera, const sf::Vector2f& target_pos, float delay_time = 0, std::function<void()> callback = nullptr);
        State* update(Camera &camera, double dt) override;

    private:
        std::function<void()> m_callback;
        sf::Vector2f m_start_pos;
        sf::Vector2f m_target_pos;
        float m_delay_time;
        float m_duration;
        float m_total_ellapsed;
    };

    class IdleState : public State
    {
    };

private:
    sf::RenderWindow* m_window;
    sf::View m_camera;
    sf::Vector2u m_size;
    State* m_current_state;
};


#endif //PLATFORMER_CAMERA_HPP
