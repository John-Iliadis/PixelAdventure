//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_MAIN_MENU_STATE_HPP
#define PLATFORMER_MAIN_MENU_STATE_HPP

#include "../scrolling_background/scrolling_background.hpp"
#include "state.hpp"
#include "../camera/camera.hpp"
#include "../gui/text_button.hpp"
#include "../asset_managers/font_manager.hpp"


class MainMenuState : public State
{
public:
    MainMenuState(StateStack& state_stack, GameContext& context, UINT_PTR user_ptr = 0);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    ScrollingBackground m_scrolling_background;
    TextButton m_button;
};


#endif //PLATFORMER_MAIN_MENU_STATE_HPP
