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
    m_checkpoints.push_back(std::move(checkpoint));
}

void CheckpointManager::update(Player &player, double dt)
{
    for (int i = 0; i < m_checkpoints.size(); ++i)
    {
        auto& checkpoint = m_checkpoints.at(i);

        if (!checkpoint.is_active() && player.get_collider().intersects(checkpoint.get_collider()))
        {
            if (m_current_active_index != -1)
            {
                m_checkpoints.at(m_current_active_index).deactivate();
            }

            m_current_active_index = i;

            checkpoint.activate();
            SoundPlayer::play_sound("checkpoint");

            player.set_respawn_position(checkpoint.get_position());
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
