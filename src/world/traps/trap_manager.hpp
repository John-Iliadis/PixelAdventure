//
// Created by Gianni on 2/02/2024.
//

#ifndef PLATFORMER_TRAP_MANAGER_HPP
#define PLATFORMER_TRAP_MANAGER_HPP

#include <vector>
#include <memory>
#include "../player/player.hpp"
#include "trap.hpp"


class TrapManager : public sf::Drawable
{
public:
    TrapManager() = default;

    void push_back(std::unique_ptr<Trap>&& trap);

    void update(Player& player, double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<std::unique_ptr<Trap>> m_traps;
};


#endif //PLATFORMER_TRAP_MANAGER_HPP
