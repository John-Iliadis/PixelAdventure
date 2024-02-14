//
// Created by Gianni on 13/02/2024.
//

#ifndef PLATFORMER_SOUND_PLAYER_HPP
#define PLATFORMER_SOUND_PLAYER_HPP

#include <cstdint>
#include <forward_list>
#include <string>
#include <ranges>
#include <SFML/Audio/Sound.hpp>
#include "../asset_managers/sound_buffer_manager.hpp"


class SoundPlayer
{
public:
    SoundPlayer() = default;

    static void play_sound(const std::string& sound_id);

    static void update(const SoundBufferManager& sound_buffers, float volume);

private:
    static std::forward_list<sf::Sound> m_sounds;
    static std::vector<std::string> m_pending_sounds;
};



#endif //PLATFORMER_SOUND_PLAYER_HPP
