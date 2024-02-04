//
// Created by Gianni on 4/02/2024.
//

#include "fruit_manager.hpp"


/* -- Fruit Manager -- */
FruitManager::FruitManager(const nlohmann::json& fruit_layer, const TextureManager& textures)
{
    m_collected_texture = &textures.get("collected");

    m_fruit_textures.push_back(&textures.get("apple"));
    m_fruit_textures.push_back(&textures.get("cherry"));
    m_fruit_textures.push_back(&textures.get("kiwi"));
    m_fruit_textures.push_back(&textures.get("melon"));
    m_fruit_textures.push_back(&textures.get("orange"));
    m_fruit_textures.push_back(&textures.get("pineapple"));
    m_fruit_textures.push_back(&textures.get("strawberry"));

    for (const auto& sub_layer : fruit_layer["layers"])
    {
        int random_fruit_texture_index = utils::random(0, m_fruit_textures.size() - 1);

        auto fruit_texture = m_fruit_textures.at(random_fruit_texture_index);

        for (const auto& object : sub_layer["objects"])
        {
            sf::Vector2f position {
                object["x"].get<float>() + object["width"].get<float>() / 2.f,
                object["y"].get<float>() + object["height"].get<float>() / 2.f
            };

            m_fruits.emplace_back(*fruit_texture, position);
        }
    }
}

void FruitManager::update(Player& player, double dt)
{
    for (auto fruit = m_fruits.begin(); fruit != m_fruits.end();)
    {
        fruit->update(dt);

        if (player.get_collider().intersects(fruit->get_collider()))
        {
            m_collected_animations.emplace_back(*m_collected_texture, fruit->get_position());
            fruit = m_fruits.erase(fruit);
        }
        else
        {
            ++fruit;
        }
    }

    for (auto collected_animation = m_collected_animations.begin(); collected_animation != m_collected_animations.end();)
    {
        collected_animation->update(dt);

        if (collected_animation->finished())
        {
            collected_animation = m_collected_animations.erase(collected_animation);
        }
        else
        {
            ++collected_animation;
        }
    }
}

void FruitManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& fruit : m_fruits)
        target.draw(fruit);

    for (const auto& collected_animation: m_collected_animations)
        target.draw(collected_animation);
}


/* -- Collected animation -- */
FruitManager::CollectedAnimation::CollectedAnimation(const sf::Texture& texture, const sf::Vector2f& pos)
{
    m_animation = Animation(32, 32, 6, sf::milliseconds(50), false);

    m_sprite.setTexture(texture);
    m_sprite.setPosition(pos);
    m_sprite.setTextureRect(m_animation.get_current_frame_rect());
    utils::set_origin(m_sprite, Origin::CENTER);
}

void FruitManager::CollectedAnimation::update(double dt)
{
    m_animation.update(dt);
    m_sprite.setTextureRect(m_animation.get_current_frame_rect());
}

bool FruitManager::CollectedAnimation::finished() const
{
    return m_animation.finished();
}


void FruitManager::CollectedAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
