//
// Created by Gianni on 29/01/2024.
//

#ifndef PLATFORMER_CAMERA_HPP
#define PLATFORMER_CAMERA_HPP

#include <cstdint>
#include <functional>
#include <cmath>
#include <memory>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include "../utilities/utils.hpp"


class Camera
{
public:
    Camera() = default;
    Camera(uint32_t width, uint32_t height);

    void update(double dt);

    void set_target(const sf::Vector2f& target, float delay_time = 0, std::function<void()> callback = nullptr);

    void set_size(uint32_t width, uint32_t height);
    void set_size(const sf::Vector2u& size);
    void set_center(float x, float y);
    void set_center(const sf::Vector2f& center);

    const sf::View& get_view() const;
    sf::Vector2f get_center() const;
    sf::Vector2f get_size() const;

private:
    class State
    {
    public:
        virtual ~State() = default;
        virtual std::unique_ptr<State> update(Camera& camera, double dt) { return nullptr; };
    };

    class TargetTransitionState : public State
    {
    public:
        TargetTransitionState(Camera& camera, const sf::Vector2f& target_pos, float delay_time = 0, std::function<void()> callback = nullptr);
        std::unique_ptr<State> update(Camera &camera, double dt) override;

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
    sf::View m_view;
    sf::Vector2u m_size;
    std::unique_ptr<State> m_current_state;
};


#endif //PLATFORMER_CAMERA_HPP
