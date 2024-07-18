//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_GAME_OVER_STATE_HPP
#define PLATFORMER_GAME_OVER_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../camera/camera.hpp"
#include "../world/parallel_task.hpp"
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
    void restart_callback();
    void main_menu_callback();
    void exit_callback();
};


#endif //PLATFORMER_GAME_OVER_STATE_HPP
