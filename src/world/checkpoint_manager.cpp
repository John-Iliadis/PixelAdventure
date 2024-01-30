//
// Created by Gianni on 30/01/2024.
//

#include "checkpoint_manager.hpp"


CheckpointManager::CheckpointManager()
    : m_current_active_index(-1)
{
}

void CheckpointManager::push_back(Checkpoint&& checkpoint)
{
    m_checkpoints.push_back(checkpoint);
}

void CheckpointManager::update(Player &player, double dt)
{
    for (int i = 0; i < m_checkpoints.size(); ++i)
    {
        auto& checkpoint = m_checkpoints.at(i);

        if (player.get_collider().intersects(checkpoint.get_collider()) && !checkpoint.is_active())
        {
            if (m_current_active_index != -1)
            {
                m_checkpoints.at(m_current_active_index).deactivate();
            }

            m_current_active_index = i;

            checkpoint.activate();
        }

        checkpoint.update(dt);
    }
}

void CheckpointManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto& checkpoint : m_checkpoints)
        target.draw(checkpoint);
}

bool CheckpointManager::empty() const
{
    return m_checkpoints.empty();
}

sf::Vector2f CheckpointManager::get_current_checkpoint_pos() const
{
    assert(m_current_active_index != -1);

    return m_checkpoints.at(m_current_active_index).get_position();
}
