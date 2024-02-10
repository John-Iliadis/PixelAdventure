//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_SETTINGS_STATE_HPP
#define PLATFORMER_SETTINGS_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "state.hpp"
#include "../gui/gui_includes.hpp"
#include "../structs/colors.hpp"


class SettingsState : public State
{
public:
    SettingsState(StateStack& state_stack, GameContext& context, UINT_PTR user_ptr = 0);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    void setup_gui();

private:
    std::unique_ptr<GUI_Container> m_gui_container;
    float place_holder_1;
    float place_holder_2;
};


#endif //PLATFORMER_SETTINGS_STATE_HPP
