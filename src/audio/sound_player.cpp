//
// Created by Gianni on 13/02/2024.
//

#include "sound_player.hpp"


std::forward_list<sf::Sound> SoundPlayer::m_sounds;
std::vector<std::string> SoundPlayer::m_pending_sounds;

void SoundPlayer::play_sound(const std::string &sound_id)
{
    if (!std::ranges::contains(m_pending_sounds, sound_id))
    {
        m_pending_sounds.push_back(sound_id);
    }
}

void SoundPlayer::update(const SoundBufferManager &sound_buffers, float volume)
{
    m_sounds.remove_if([] (const sf::Sound& sound) {
        return sound.getStatus() == sf::SoundSource::Stopped;
    });

    if (m_pending_sounds.empty()) return;

    for (const auto& pending_sound_id : m_pending_sounds)
    {
        const sf::SoundBuffer& sound_buffer = sound_buffers.get(pending_sound_id);

        m_sounds.emplace_front(sound_buffer);
        m_sounds.front().setVolume(volume);
        m_sounds.front().play();
    }

    m_pending_sounds.clear();
}
