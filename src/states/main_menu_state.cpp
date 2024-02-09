//
// Created by Gianni on 12/01/2024.
//

#include "main_menu_state.hpp"

#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>


MainMenuState::MainMenuState(StateStack &state_stack, GameContext& context, UINT_PTR user_ptr)
    : State(state_stack, context)
{
    sf::Texture& bg_texture = m_context.texture_manager->get("blue");
    sf::Vector2i bg_size = static_cast<sf::Vector2i>(m_context.world_camera->get_size());

    m_scrolling_background = ScrollingBackground(bg_texture, bg_size);

    setup_gui();
}

bool MainMenuState::handle_events(const sf::Event &event)
{


    return false;
}

bool MainMenuState::update(double dt)
{
    m_scrolling_background.update(dt);

    return false;
}

void MainMenuState::on_world_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_scrolling_background);
}

void MainMenuState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_gui_container);
}

void MainMenuState::setup_gui()
{
    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

    float window_width = window_size.x;
    float window_height = window_size.y;

    auto& textures = *m_context.texture_manager;
    auto& fonts = *m_context.font_manager;

    m_gui_container.set_container_texture(textures.get("settings_board"));
    m_gui_container.set_container_origin(Origin::CENTER);
    m_gui_container.set_container_position(window_width / 2, window_height / 2 + 80);
    m_gui_container.set_container_scale(3, 3);

    sf::Sprite title_banner_sprite(textures.get("title_board"));
    title_banner_sprite.setScale(3, 3);
    title_banner_sprite.setPosition(window_width / 2, 150);
    utils::set_origin(title_banner_sprite, Origin::CENTER);

    sf::Text title_banner_text("Settings", fonts.get("pixel_type"), 50);
    title_banner_text.setPosition(title_banner_sprite.getPosition());
    title_banner_text.setFillColor(sf::Color::Black);
    utils::center_text(title_banner_text);

    auto title_banner_el = std::make_unique<SpriteElement>(title_banner_sprite);
    auto title_banner_text_el = std::make_unique<TextElement>(title_banner_text);

    m_gui_container.push_back(std::move(title_banner_el));
    m_gui_container.push_back(std::move(title_banner_text_el));
}
