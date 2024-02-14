//
// Created by Gianni on 13/02/2024.
//

#ifndef PLATFORMER_MUSIC_PLAYER_HPP
#define PLATFORMER_MUSIC_PLAYER_HPP

#include <SFML/Audio/Music.hpp>
#include <memory>
#include "../asset_managers/music_manager.hpp"


class MusicPlayer
{
public:
    static void play(const std::string& music_id, bool looped);

    static void pause();
    static void unpause();
    static void stop();

    static void update(MusicManager& music_manager, float volume);

private:
    struct PendingChange
    {
        std::string music_id;
        bool looped;
    };

    static sf::Music* m_music;
    static std::unique_ptr<PendingChange> m_pending_change;
};


#endif //PLATFORMER_MUSIC_PLAYER_HPP
