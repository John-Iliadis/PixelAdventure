//
// Created by Gianni on 18/01/2024.
//

#ifndef PLATFORMER_PLAYER_STATE_HPP
#define PLATFORMER_PLAYER_STATE_HPP

#include <SFML/Window/Event.hpp>


class Player;

class PlayerState
{
public:
    virtual ~PlayerState() = default;

    virtual void on_enter(Player& player) = 0;
    virtual void on_exit(Player& player) = 0;

    virtual PlayerState* handle_event(Player& player, const sf::Event& event) = 0;
    virtual PlayerState* update(Player& player, double dt) = 0;
};

#endif //PLATFORMER_PLAYER_STATE_HPP
