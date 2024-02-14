//
// Created by Gianni on 4/02/2024.
//

#ifndef PLATFORMER_FRUIT_MANAGER_HPP
#define PLATFORMER_FRUIT_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include "../../utilities/utils.hpp"
#include "../../vendor/json.hpp"
#include "../../audio/sound_player.hpp"
#include "../player/player.hpp"
#include "fruit.hpp"


class FruitManager : public sf::Drawable
{
public:
    FruitManager() = default;
    FruitManager(const nlohmann::json& fruit_layer, const TextureManager& textures);

    void update(Player& player, double dt);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    class CollectedAnimation : public sf::Drawable
    {
    public:
        CollectedAnimation() = default;
        CollectedAnimation(const sf::Texture& texture, const sf::Vector2f& pos);

        void update(double dt);

        bool finished() const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Sprite m_sprite;
        Animation m_animation;
    };

    std::vector<const sf::Texture*> m_fruit_textures;
    std::vector<Fruit> m_fruits;

    const sf::Texture* m_collected_texture;
    std::vector<CollectedAnimation> m_collected_animations;
};


#endif //PLATFORMER_FRUIT_MANAGER_HPP
