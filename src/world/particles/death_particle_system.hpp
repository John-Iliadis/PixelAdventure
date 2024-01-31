//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_DEATH_PARTICLE_SYSTEM_HPP
#define PLATFORMER_DEATH_PARTICLE_SYSTEM_HPP

#include <unordered_map>
#include <vector>
#include "../enums.hpp"
#include "death_particle.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "../../vendor/json.hpp"


class DeathParticleSystem : public sf::Drawable
{
public:
    DeathParticleSystem(const TextureManager& texture_manager);

    void add_particle(ParticleType particle, const sf::Vector2f& pos, const sf::Vector2f& velocity, Orientation orientation);
    void update(double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<DeathParticle> m_particles;
    std::unordered_map<std::string, Animation> m_animations;
    std::unordered_map<std::string, const sf::Texture*> m_textures;
};


#endif //PLATFORMER_DEATH_PARTICLE_SYSTEM_HPP
