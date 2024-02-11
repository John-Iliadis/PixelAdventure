//
// Created by Gianni on 12/01/2024.
//

#ifndef PLATFORMER_STATE_STACK_HPP
#define PLATFORMER_STATE_STACK_HPP

#include <vector>
#include <memory>
#include <ranges>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../enums/state_identifiers.hpp"
#include "game_context.hpp"
#include "state_factory.hpp"
#include "state.hpp"
#include "../camera/camera.hpp"


class StateStack
{
public:
    StateStack();
    StateStack(GameContext& context);

    void handle_events(const sf::Event& event);
    void update(double dt);
    void draw();

    void push(StateID id, UINT_PTR user_ptr = 0);
    void pop();
    void clear();
    void apply_pending_changes();

    bool empty() const;

    StateStack(StateStack&&) = delete;
    StateStack& operator=(StateStack&& other) noexcept;

private:
    enum class Action
    {
        NONE,
        PUSH,
        POP,
        CLEAR
    };

    struct PendingChange
    {
        Action action;
        StateID id;
        UINT_PTR user_ptr;

        PendingChange(Action action = Action::NONE, StateID id = StateID::NONE, UINT_PTR user_ptr = 0)
            : action(action), id(id), user_ptr(user_ptr) {}
    };

private:
    GameContext* m_context;
    std::vector<std::unique_ptr<State>> m_state_stack;
    std::vector<PendingChange> m_pending_changes;
    StateFactory m_state_factory;
};


#endif //PLATFORMER_STATE_STACK_HPP
