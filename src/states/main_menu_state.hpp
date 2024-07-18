//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_MAIN_MENU_STATE_HPP
#define PLATFORMER_MAIN_MENU_STATE_HPP

#include "../scrolling_background/scrolling_background.hpp"
#include "../camera/camera.hpp"
#include "../asset_managers/font_manager.hpp"
#include "../asset_managers/texture_manager.hpp"
#include "../structs/colors.hpp"
#include "../world/parallel_task.hpp"
#include "state.hpp"

#include "../gui/gui_sprite.hpp"
#include "../gui/gui_container.hpp"
#include "../gui/gui_slider.hpp"
#include "../gui/gui_text.hpp"
#include "../gui/gui_button.hpp"


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
    void play_callback();
    void settings_callback();
    void exit_callback();

private:
    ScrollingBackground m_scrolling_background;
    GUI_Container m_container;
    GUI_Button* m_button;
    float val;
};


#endif //PLATFORMER_MAIN_MENU_STATE_HPP
