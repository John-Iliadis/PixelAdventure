//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

// todo: clean up includes
#include <functional>
#include <fstream>
#include <thread>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "../../states/game_context.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "../../asset_managers/sound_buffer_manager.hpp"
#include "../../utilities/utils.hpp"
#include "idle_state.hpp"
#include "../sprite_collider.hpp"
#include "../../animation/animation_manager.hpp"
#include "../enums.hpp"


class Player : public sf::Drawable
{
public:
    Player(); // todo: pass map data for world scale
    ~Player();

    void handle_event(const sf::Event& event);
    void update(double dt);

    void set_collision_callbacks(std::function<void(double)> x, std::function<void(double)> y);

    void set_animation(const std::string& id);
    void set_position(float x, float y);
    void set_velocity(float x, float y);
    void move(float x, float y);
    void jump();
    void set_gravity(bool on);
    void set_previously_jumped(bool prev_jumped);
    void set_previously_double_jumped(bool prev_double_jumped);
    void set_touching_wall(bool touching_wall);

    sf::FloatRect get_hitbox() const;
    sf::Vector2f get_center() const;
    sf::Vector2f get_position() const;
    SpriteOrientation get_orientation() const;

    sf::Vector2f get_velocity() const;
    float get_wall_sliding_speed() const;
    float get_jump_pressed_remember_time() const;
    bool previously_jumped() const;
    bool previously_double_jumped() const;
    bool touching_wall() const;
    sf::Time time_since_last_jump_button_pressed() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void handle_real_time_input();
    void apply_gravity();
    void change_state(PlayerState* new_state);
    void set_animation_frame();
    void init_platformer_data();

private:
    TextureManager m_textures;
    SoundBufferManager m_sound_buffers;
    SpriteCollider m_sprite_collider;
    AnimationManager m_animations;
    PlayerState* current_state;

    std::function<void(double)> x_axis_collision_callback;
    std::function<void(double)> y_axis_collision_callback;

private:
    sf::Vector2f m_velocity;
    float m_move_speed;
    float m_gravity;
    float m_gravity_speed;
    float m_wall_sliding_speed;
    float m_jump_speed;
    float m_jump_pressed_remember_time;
    bool m_previously_jumped;
    bool m_previously_double_jumped;
    bool m_touching_wall;
    sf::Clock m_time_since_last_jump_button_pressed;
};


#endif //PLATFORMER_PLAYER_HPP
