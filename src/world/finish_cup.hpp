//
// Created by Gianni on 15/02/2024.
//

#ifndef PLATFORMER_FINISH_CUP_HPP
#define PLATFORMER_FINISH_CUP_HPP

#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../animation/animation_manager.hpp"
#include "../asset_managers/texture_manager.hpp"
#include "../audio/sound_player.hpp"
#include "../audio/music_player.hpp"
#include "../utilities/utils.hpp"
#include "player/player.hpp"


class FinishCup : public sf::Drawable
{
public:
    FinishCup() = default;
    FinishCup(const TextureManager& textures, const sf::Vector2f& position);

    void update(Player& player, double dt);

    bool triggered() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    enum class State
    {
        IDLE,
        TRIGGERED
    } m_current_state;

    sf::Sprite m_sprite;
    AnimationManager m_animations;
    std::unordered_map<std::string, const sf::Texture*> m_textures;
};


#endif //PLATFORMER_FINISH_CUP_HPP
