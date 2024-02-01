//
// Created by Gianni on 1/02/2024.
//

#include "fire_trap_manager.hpp"


void FireTrapManager::push_back(FireTrap&& fire_trap)
{
    m_fire_traps.push_back(std::move(fire_trap));
}

void FireTrapManager::update(Player &player, double dt)
{
    for (auto& fire_trap : m_fire_traps)
    {
        fire_trap.update(dt);

        if (player.get_collider().intersects(fire_trap.get_collider()) && player.is_alive())
        {
            player.die();
        }
    }
}

void FireTrapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& spike : m_fire_traps)
        target.draw(spike);
}
