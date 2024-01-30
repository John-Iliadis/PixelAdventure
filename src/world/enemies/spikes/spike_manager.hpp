//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_SPIKE_MANAGER_HPP
#define PLATFORMER_SPIKE_MANAGER_HPP

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include "spike.hpp"
#include "../../player/player.hpp"

class SpikeManager : public sf::Drawable
{
public:
    SpikeManager() = default;

    void push_back(Spike&& spike);
    void handle_collisions(Player& player);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<Spike> m_spikes;
};


#endif //PLATFORMER_SPIKE_MANAGER_HPP
