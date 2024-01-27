//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "idle_state.hpp"
#include "player_data.hpp"
#include "../sprite_collider.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "../../asset_managers/sound_buffer_manager.hpp"
#include "../../animation/animation_manager.hpp"
#include "../../utilities/utils.hpp"


class Player : public sf::Drawable
{
public:
    Player();
    ~Player();

    void handle_events(const sf::Event& event);
    void update(double dt);

    void set_animation(const std::string& id);
    void set_position(float x, float y);
    void set_position(const sf::Vector2f& pos);
    void set_velocity(float x, float y);
    void move(float x, float y);
    void jump();
    void set_gravity(bool on);
    void set_previously_jumped(bool prev_jumped);
    void set_previously_double_jumped(bool prev_double_jumped);
    void set_touching_wall(bool touching_wall);
    void set_orientation(Orientation orientation);
    void set_collision_callback(std::function<void(double)> callback);

    sf::FloatRect get_collider() const;
    sf::Vector2f get_center() const;
    sf::Vector2f get_position() const;
    sf::Vector2f get_velocity() const;
    Orientation get_orientation() const;
    float get_wall_sliding_speed() const;
    float get_jump_pressed_ellapsed_time() const;
    bool previously_jumped() const;
    bool previously_double_jumped() const;
    bool touching_wall() const;

private:
    void handle_input();
    void update_physics(double dt);
    void handle_state();
    void update_animation(double dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void apply_gravity();
    void change_state(PlayerState* new_state);
    void set_animation_frame();

private:
    PlayerData m_player_data;
    TextureManager m_textures;
    SoundBufferManager m_sound_buffers;
    SpriteCollider m_sprite_collider;
    Orientation m_orientation;
    AnimationManager m_animations;
    PlayerState* m_current_state;
    std::function<void(double)> m_resolve_collision_callback;
};


#endif //PLATFORMER_PLAYER_HPP
