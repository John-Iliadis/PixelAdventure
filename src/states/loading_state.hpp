//
// Created by Gianni on 13/02/2024.
//

#ifndef PLATFORMER_LOADING_STATE_HPP
#define PLATFORMER_LOADING_STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "state.hpp"


class LoadingState : public State
{
public:
    LoadingState(StateStack& state_stack, GameContext& context, void* user_ptr = nullptr);

    bool handle_events(const sf::Event &event) override;
    bool update(double dt) override;
    void on_world_draw() override;
    void on_gui_draw() override;

private:
    sf::Text m_loading_text;
};



#endif //PLATFORMER_LOADING_STATE_HPP
