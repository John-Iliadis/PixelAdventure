//
// Created by Gianni on 10/02/2024.
//

#ifndef PLATFORMER_KEY_BINDING_STATE_HPP
#define PLATFORMER_KEY_BINDING_STATE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../structs/colors.hpp"
#include "../utilities/utils.hpp"
#include "../structs/settings.hpp"
#include "../audio/sound_player.hpp"
#include "state.hpp"


class KeyBindingState : public State
{
public:
    KeyBindingState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    bool check_valid_key(sf::Keyboard::Key key);

    void back_callback();

private:
    std::unique_ptr<std::string> m_action;
    sf::Text m_invalid_key_text;
    float m_invalid_key_timer;
};


#endif //PLATFORMER_KEY_BINDING_STATE_HPP
