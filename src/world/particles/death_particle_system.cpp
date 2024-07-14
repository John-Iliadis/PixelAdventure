//
// Created by Gianni on 30/01/2024.
//

#include "death_particle_system.hpp"


static const std::string animation_file_path = "../data/death_particles/animations.json";

DeathParticleSystem::DeathParticleSystem(const TextureManager &texture_manager)
{
    std::ifstream file(animation_file_path);

    nlohmann::json json = nlohmann::json::parse(file);

    file.close();

    for (const auto& animation : json)
    {
        Animation l_animation {
            animation["sprite_width"].get<int>(),
            animation["sprite_height"].get<int>(),
            animation["frame_count"].get<uint32_t>(),
            sf::milliseconds(animation["frame_time_milliseconds"].get<int>()),
            animation["looped"].get<bool>()
        };

        std::string l_id = animation["id"].get<std::string>();

        m_animations.emplace(std::make_pair(std::move(l_id), std::move(l_animation)));
    }

    m_textures["player_death"] = &texture_manager.get("player_death");
}

void DeathParticleSystem::add_particle(ParticleType particle, const sf::Vector2f &pos, const sf::Vector2f &velocity, Orientation orientation)
{
    switch (particle)
    {
        case ParticleType::PLAYER_DEATH:
            m_particles.emplace_back(m_animations["player_death"], *m_textures["player_death"], pos, velocity, orientation);
            break;
    }
}

void DeathParticleSystem::update(double dt)
{
    for (auto itr = m_particles.begin(); itr != m_particles.end();)
    {
        if (itr->finished())
        {
            itr = m_particles.erase(itr);
        }
        else
        {
            itr->update(dt);
            ++itr;
        }
    }
}

void DeathParticleSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& particle : m_particles)
        target.draw(particle);
}
