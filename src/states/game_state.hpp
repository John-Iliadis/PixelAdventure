//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_GAME_STATE_HPP
#define PLATFORMER_GAME_STATE_HPP

#include "state.hpp"
#include "../world/world.hpp"
#include "../audio/music_player.hpp"


class GameState : public State
{
public:
    GameState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    std::unique_ptr<World> m_world;
};


#endif //PLATFORMER_GAME_STATE_HPP
