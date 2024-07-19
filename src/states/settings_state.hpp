//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_SETTINGS_STATE_HPP
#define PLATFORMER_SETTINGS_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "state.hpp"
#include "../asset_managers/texture_manager.hpp"
#include "../asset_managers/font_manager.hpp"
#include "../structs/settings.hpp"
#include "../gui/includes.hpp"


class SettingsState : public State
{
public:
    SettingsState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    void on_return() override;

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    void left_binding_callback();
    void right_binding_callback();
    void up_binding_callback();
    void back_callback();
    void build_gui();

private:
    GUI_Container m_banner;
    GUI_Container m_left_panel;
    GUI_Container m_right_panel;
};


#endif //PLATFORMER_SETTINGS_STATE_HPP
