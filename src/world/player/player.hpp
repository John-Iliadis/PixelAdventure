//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

// todo: clean up includes
#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "../../states/game_context.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "../../asset_managers/sound_buffer_manager.hpp"
#include "../../utilities/utils.hpp"
#include "idle_state.hpp"
#include "player_platformer_data.hpp"
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
    void move(float x, float y);
    void set_gravity(bool on);

    sf::FloatRect get_hitbox() const;
    sf::Vector2f get_center() const;
    sf::Vector2f get_position() const;
    PlatformerData& get_platformer_data();
    SpriteOrientation get_orientation() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void handle_real_time_input();
    void apply_gravity();
    void change_state(PlayerState* new_state);
    void set_animation_frame();

private:
    TextureManager m_textures;
    SoundBufferManager m_sound_buffers;
    SpriteCollider m_sprite_collider;
    PlatformerData m_data;
    AnimationManager m_animations;
    PlayerState* current_state;

    std::function<void(double)> x_axis_collision_callback;
    std::function<void(double)> y_axis_collision_callback;
};


#endif //PLATFORMER_PLAYER_HPP
