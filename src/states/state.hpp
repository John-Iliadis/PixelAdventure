//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_STATE_HPP
#define PLATFORMER_STATE_HPP

#include <memory>
#include <basetsd.h>
#include <SFML/Window/Event.hpp>
#include "game_context.hpp"
#include "state_identifiers.hpp"


class StateStack;

class State
{
public:
    State(StateStack& state_stack, GameContext& context, UINT_PTR user_ptr = 0);
    virtual ~State() = default;

    virtual void on_exit();
    virtual void on_return();

    virtual bool handle_events(const sf::Event& event) = 0;
    virtual bool update(double dt) = 0;
    virtual void draw() = 0;

protected:
    void request_stack_push(StateID state_id);
    void request_stack_pop();
    void request_stack_clear();

protected:
    GameContext& context;

    enum class Status
    {
        CURRENT,
        OBSCURED
    } status;

private:
    StateStack& state_stack;
};


#endif //PLATFORMER_STATE_HPP
