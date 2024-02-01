//
// Created by Gianni on 1/02/2024.
//

#ifndef PLATFORMER_SAW_MANAGER_HPP
#define PLATFORMER_SAW_MANAGER_HPP

#include <memory>
#include "../../player/player.hpp"
#include "saw.hpp"

class SawManager : public sf::Drawable
{
public:
    SawManager() = default;

    void push_back(std::unique_ptr<Saw>&& saw);

    void update(Player& player, double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<std::unique_ptr<Saw>> m_saw_traps;
};


#endif //PLATFORMER_SAW_MANAGER_HPP
