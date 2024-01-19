//
// Created by Gianni on 13/01/2024.
//

#ifndef PLATFORMER_PLAYER_HPP
#define PLATFORMER_PLAYER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "../../states/game_context.hpp"
#include "../../asset_managers/texture_manager.hpp"
#include "../../asset_managers/sound_buffer_manager.hpp"
#include "idle_state.hpp"
#include "player_platformer_data.hpp"


class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player();
    ~Player();

    void update(double dt);
    void handle_event(const sf::Event& event);

    void set_texture(const std::string& texture_id);
    void set_texture_rect(const sf::IntRect& rect);


    sf::FloatRect get_rectangle() const;
    sf::Vector2f get_center() const;
    sf::Sprite& get_sprite();
    PlatformerData& get_platformer_data();
    bool facing_right();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    TextureManager m_textures;
    SoundBufferManager m_sound_buffers;
    sf::Sprite m_sprite;
    PlatformerData m_platformer_data;
    PlayerState* current_state;
};


#endif //PLATFORMER_PLAYER_HPP
