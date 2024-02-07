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

    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

    auto m_regular_button = std::make_unique<Button>();

    m_regular_button->set_position(100, 100);
    m_regular_button->set_button_texture(m_context.texture_manager->get("arrow_right"));
    m_regular_button->set_button_scale(2, 2);
    m_regular_button->set_button_hover_scale(2.5, 2.5);
    m_regular_button->set_button_origin(Origin::CENTER);
    m_regular_button->set_button_callback([] () { puts("regular_button"); });

    auto m_text_button = std::make_unique<TextButton>();
    m_text_button->set_position(window_size / 2.f);
    m_text_button->set_button_texture(m_context.texture_manager->get("big_green_button"));
    m_text_button->set_button_origin(Origin::CENTER);
    m_text_button->set_button_scale(2, 2);
    m_text_button->set_button_hover_scale(2.2, 2.2);
    m_text_button->set_button_callback([] () { puts("clicked"); });

    m_text_button->set_text_font(m_context.font_manager->get("pixel_type"));
    m_text_button->set_text_character_size(50);
    m_text_button->set_text_character_size_hover(55);
    m_text_button->set_text_color(sf::Color::Black);
    m_text_button->set_text_string("Button");
    m_text_button->set_text_offset(0, -2);

    m_gui_container.push_back(std::move(m_text_button));
    m_gui_container.push_back(std::move(m_regular_button));
}

bool MainMenuState::handle_events(const sf::Event &event)
{
    m_gui_container.handle_events(event);

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
