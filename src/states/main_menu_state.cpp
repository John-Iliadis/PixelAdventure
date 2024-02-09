//
// Created by Gianni on 12/01/2024.
//

#include "main_menu_state.hpp"


MainMenuState::MainMenuState(StateStack &state_stack, GameContext& context, UINT_PTR user_ptr)
    : State(state_stack, context)
{
    sf::Texture& bg_texture = m_context.texture_manager->get("blue");
    sf::Vector2i bg_size = static_cast<sf::Vector2i>(m_context.world_camera->get_size());

    m_scrolling_background = ScrollingBackground(bg_texture, bg_size);

    setup_gui();

    ptr = 10;
}

bool MainMenuState::handle_events(const sf::Event &event)
{
    m_gui_container->handle_event(event);

    return false;
}

bool MainMenuState::update(double dt)
{
    m_scrolling_background.update(dt);
    m_gui_container->update(sf::Mouse::getPosition(*m_context.window));

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

    window.draw(*m_gui_container);
}

void MainMenuState::setup_gui()
{
    static GUI_Builder gui_builder(m_context.texture_manager, m_context.font_manager);

    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

    float window_width = window_size.x;
    float window_height = window_size.y;

    m_gui_container = gui_builder.set_texture("menu_board")
                                 .set_position(window_width / 2, window_height / 2 + 80)
                                 .set_origin(Origin::CENTER)
                                 .set_scale(3, 3)
                                 .make_container();

    std::unique_ptr<SpriteElement> title_board = gui_builder.set_texture("title_board")
                                                            .set_position(window_width / 2.f, 100)
                                                            .set_scale(3, 3)
                                                            .make_sprite_element();
}
