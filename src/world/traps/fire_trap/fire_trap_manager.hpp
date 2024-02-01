//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_FIRE_TRAP_MANAGER_HPP
#define PLATFORMER_FIRE_TRAP_MANAGER_HPP

#include "fire_trap.hpp"
#include "../../player/player.hpp"


class FireTrapManager : public sf::Drawable
{
public:
    FireTrapManager() = default;

    void push_back(FireTrap&& fire_trap);

    void update(Player& player, double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<FireTrap> m_fire_traps;
};


#endif //PLATFORMER_FIRE_TRAP_MANAGER_HPP
