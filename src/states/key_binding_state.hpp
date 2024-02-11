//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_KEY_BINDING_STATE_HPP
#define PLATFORMER_KEY_BINDING_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../gui/gui_includes.hpp"
#include "../structs/colors.hpp"
#include "state.hpp"


class KeyBindingState : public State
{
public:
    KeyBindingState(StateStack& state_stack, GameContext& context, UINT_PTR user_ptr = 0);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    void setup_gui();

private:
    std::unique_ptr<GUI_Container> m_gui_container;
};


#endif //PLATFORMER_KEY_BINDING_STATE_HPP
