//
// Created by Gianni on 2/02/2024.
//

#include "trap_manager.hpp"


void TrapManager::push_back(std::unique_ptr<Trap>&& trap)
{
    m_traps.push_back(std::move(trap));
}

void TrapManager::update(Player &player, double dt)
{
    for (auto& trap : m_traps)
    {
        trap->update(dt);

        if (player.get_collider().intersects(trap->get_collider()))
        {
            player.die();
        }
    }
}

void TrapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& trap : m_traps)
        target.draw(*trap);
}
