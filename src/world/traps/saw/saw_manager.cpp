//
// Created by Gianni on 1/02/2024.
//

#include "saw_manager.hpp"


void SawManager::push_back(std::unique_ptr<Saw>&& saw)
{
    m_saw_traps.push_back(std::move(saw));
}

void SawManager::update(Player &player, double dt)
{
    for (auto& saw : m_saw_traps)
    {
        saw->update(dt);

        if (player.get_collider().intersects(saw->get_collider()) && player.is_alive())
        {
            player.die();
        }
    }
}

void SawManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& saw : m_saw_traps)
        target.draw(*saw);
}
