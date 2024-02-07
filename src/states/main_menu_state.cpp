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

    m_button.set_position(m_context.world_camera->get_center());

    m_button.set_button_texture(m_context.texture_manager->get("long_button"));
    m_button.set_button_origin(Origin::CENTER);
    m_button.set_button_scale(1.5, 1.5);
    m_button.set_button_callback([] () { puts("clicked"); });

    m_button.set_text_font(m_context.font_manager->get("pixel_type"));
    m_button.set_text_character_size(90);
    m_button.set_text_color(sf::Color::Black);
    m_button.set_text_string("Button");
    m_button.set_text_scale(0.2, 0.2);
    m_button.set_text_scale_hover(0.22, 0.22);
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
    window.draw(m_button);
}

void MainMenuState::on_gui_draw()
{

}
