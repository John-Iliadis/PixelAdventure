//
// Created by Gianni on 30/01/2024.
//

#include "spike_manager.hpp"


void SpikeManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& spike : m_spikes)
        target.draw(spike);
}

void SpikeManager::push_back(Spike&& spike)
{
    m_spikes.push_back(std::move(spike));
}

void SpikeManager::handle_collisions(Player &player)
{
    for (const auto& spike : m_spikes)
    {
        if (player.get_collider().intersects(spike.get_collider()) && player.is_alive())
        {
            player.die();
        }
    }
}
