//
// Created by Gianni on 2/02/2024.
//

#ifndef PLATFORMER_SPIKE_HEAD_HPP
#define PLATFORMER_SPIKE_HEAD_HPP

#include <vector>
#include <unordered_map>
#include "../../../asset_managers/texture_manager.hpp"
#include "../../../animation/animation_manager.hpp"
#include "../../../utilities/utils.hpp"
#include "../../sprite_collider.hpp"
#include "../trap.hpp"


class SpikeHead : public Trap
{
public:
    SpikeHead(const TextureManager& textures);

    void set_path(std::vector<sf::Vector2f>&& path);
    void set_spawn_pos_index(uint8_t index);

    void update(double dt) override;

    sf::FloatRect get_collider() const override;

private:
    enum class State
    {
        MOVING,
        STOPPING
    } m_current_state;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update_moving_state(double dt);
    void update_stopping_state(double dt);
    void update_animation(double dt);
    void calculate_duration();

    void on_moving_exit(const std::string& animation_name);
    void on_stopping_exit();

private:
    AnimationManager m_animations;
    SpriteCollider m_sprite_collider;
    std::unordered_map<std::string, const sf::Texture*> m_textures;
    std::vector<sf::Vector2f> m_path;
    uint8_t m_start_pos_index;
    uint8_t m_target_pos_index;
    double m_ellapsed;
    double m_duration;
};


#endif //PLATFORMER_SPIKE_HEAD_HPP
