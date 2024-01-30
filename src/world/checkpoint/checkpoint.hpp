//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_CHECKPOINT_HPP
#define PLATFORMER_CHECKPOINT_HPP

#include <unordered_map>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../../animation/animation_manager.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "../../asset_managers/sound_buffer_manager.hpp"
#include "../sprite_collider.hpp"
#include "../player/player.hpp"


class Checkpoint : public sf::Drawable
{
public:
    Checkpoint(const TextureManager& texture_manager);

    void activate();
    void deactivate();

    void set_position(float x, float y);
    void set_position(const sf::Vector2f& pos);

    void update(double dt);

    sf::FloatRect get_collider() const;
    sf::Vector2f get_position() const;
    bool is_active() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    enum class State
    {
        IDLE,
        TRIGGERED,
        FLAG_OUT
    } m_current_state;

    void on_idle_enter();
    void on_triggered_enter();
    void on_flag_out_enter();
    void set_animation(const std::string& id);

private:
    SpriteCollider m_sprite;
    AnimationManager m_animations;
    std::unordered_map<std::string, const sf::Texture*> m_textures;
    std::unordered_map<std::string, const sf::SoundBuffer*> m_sound_buffers;
};


#endif //PLATFORMER_CHECKPOINT_HPP
