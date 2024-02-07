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

    m_button.set_position(window_size / 2.f);

    m_button.set_button_texture(m_context.texture_manager->get("big_green_button"));
    m_button.set_button_origin(Origin::CENTER);
    m_button.set_button_scale(2, 2);
    m_button.set_button_hover_scale(2.2, 2.2);
    m_button.set_button_callback([] () { puts("clicked"); });

    m_button.set_text_font(m_context.font_manager->get("pixel_type"));
    m_button.set_text_character_size(50);
    m_button.set_text_character_size_hover(55);
    m_button.set_text_color(sf::Color::Black);
    m_button.set_text_string("Button");
}

bool MainMenuState::handle_events(const sf::Event &event)
{
    return false;
}

bool MainMenuState::update(double dt)
{
    m_scrolling_background.update(dt);

    sf::Vector2i pixel_pos = sf::Mouse::getPosition(*m_context.window);
    sf::Vector2f world_pos = m_context.window->mapPixelToCoords(pixel_pos);

    if (m_button.get_clickable_area().contains(world_pos))
    {
        m_button.select();
    }
    else
    {
        m_button.deselect();
    }

    if (m_button.selected() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_button.activate();
    }
    else
    {
        m_button.deactivate();
    }

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

    window.draw(m_button);
}
