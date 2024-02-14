//
// Created by Gianni on 30/01/2024.
//

#ifndef PLATFORMER_CHECKPOINT_MANAGER_HPP
#define PLATFORMER_CHECKPOINT_MANAGER_HPP

#include <vector>
#include <cassert>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../../audio/sound_player.hpp"
#include "../player/player.hpp"
#include "checkpoint.hpp"


class CheckpointManager : public sf::Drawable
{
public:
    CheckpointManager();

    void push_back(Checkpoint&& checkpoint);
    void update(Player& player, double dt);

    bool empty() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<Checkpoint> m_checkpoints;
    int m_current_active_index;
};


#endif //PLATFORMER_CHECKPOINT_MANAGER_HPP
