//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

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


class Player : public sf::Drawable
{
public:
    Player(); // todo: pass map data for world scale
    ~Player();

    void update(double dt);
    void handle_event(const sf::Event& event);

    void set_collision_callbacks(std::function<void(double)> x, std::function<void(double)> y);

    void set_texture(const std::string& texture_id);
    void set_texture_rect(const sf::IntRect& rect);
    void set_position(float x, float y);
    void move(float x, float y);
    void set_gravity(bool on);

    sf::FloatRect get_rectangle() const;
    sf::Vector2f get_center() const; // update to new center
    sf::Vector2f get_position() const;
    sf::Sprite& get_sprite();
    PlatformerData& get_platformer_data();
    bool facing_right();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void handle_real_time_input();
    void apply_gravity();
    void change_state(PlayerState* new_state);

private:
    TextureManager m_textures;
    SoundBufferManager m_sound_buffers;
    sf::Sprite m_sprite;
    PlatformerData m_platformer_data;
    PlayerState* current_state;

    std::function<void(double)> x_axis_collision_callback;
    std::function<void(double)> y_axis_collision_callback;
};


#endif //PLATFORMER_PLAYER_HPP
