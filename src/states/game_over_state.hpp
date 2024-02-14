//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_GAME_OVER_STATE_HPP
#define PLATFORMER_GAME_OVER_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../gui/gui_includes.hpp"
#include "../structs/colors.hpp"
#include "../structs/level_details.hpp"
#include "state.hpp"


class GameOverState : public State
{
public:
    GameOverState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    void setup_gui();

private:
    GUI_Container m_gui_container;
};


#endif //PLATFORMER_GAME_OVER_STATE_HPP
