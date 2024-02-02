//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_FIRE_TRAP_HPP
#define PLATFORMER_FIRE_TRAP_HPP

#include <unordered_map>
#include "../../../asset_managers/texture_manager.hpp"
#include "../../../animation/animation_manager.hpp"
#include "../../sprite_collider.hpp"
#include "../trap.hpp"


class FireTrap : public Trap
{
public:
    FireTrap(const TextureManager& textures);

    void place(const sf::Vector2f& pos, int rotation);
    void set_timer(float on_time, float off_time);

    void update(double dt) override;

    sf::Rect<float> get_collider() const override;

private:
    void update_animation(double dt);
    void on_fire_on_exit();
    void on_fire_off_exit();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    enum class State
    {
        FIRE_ON,
        FIRE_OFF
    } m_current_state;

private:
    SpriteCollider m_sprite_collider;
    AnimationManager m_animations;
    std::unordered_map<std::string, const sf::Texture*> m_textures;

    float m_on_time;
    float m_off_time;
    double m_ellapsed;
};


#endif //PLATFORMER_FIRE_TRAP_HPP
