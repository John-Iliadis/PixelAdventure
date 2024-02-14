//
// Created by Gianni on 13/02/2024.
//

#include "music_player.hpp"


sf::Music* MusicPlayer::m_music = nullptr;
std::unique_ptr<MusicPlayer::PendingChange> MusicPlayer::m_pending_change;

void MusicPlayer::play(const std::string &music_id, bool looped)
{
    m_pending_change = std::make_unique<PendingChange>(music_id, looped);
}

void MusicPlayer::pause()
{
    if (m_music) m_music->pause();
}

void MusicPlayer::unpause()
{
    if (m_music) m_music->play();
}

void MusicPlayer::stop()
{
    if (m_music) m_music->stop();
}

void MusicPlayer::update(MusicManager &music_manager, float volume)
{
    if (m_pending_change)
    {
        if (m_music) m_music->stop();

        m_music = &music_manager.get(m_pending_change->music_id);
        m_music->setLoop(m_pending_change->looped);
        m_music->play();

        m_pending_change.release();
    }

    if (m_music && m_music->getVolume() != volume)
    {
        m_music->setVolume(volume);
    }
}
