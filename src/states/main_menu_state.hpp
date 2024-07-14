//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_MAIN_MENU_STATE_HPP
#define PLATFORMER_MAIN_MENU_STATE_HPP

#include "../scrolling_background/scrolling_background.hpp"
#include "../camera/camera.hpp"
#include "../asset_managers/font_manager.hpp"
#include "../asset_managers/texture_manager.hpp"
#include "../gui/gui_includes.hpp"
#include "../structs/colors.hpp"
#include "../audio/music_player.hpp"
#include "state.hpp"


class MainMenuState : public State
{
public:
    MainMenuState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    void on_exit() override;
    void on_return() override;

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    void setup_gui();

private:
    ScrollingBackground m_scrolling_background;
    GUI_Container m_gui_container;
};


#endif //PLATFORMER_MAIN_MENU_STATE_HPP
