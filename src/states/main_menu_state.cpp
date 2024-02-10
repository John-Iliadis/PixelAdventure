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

    m_gui_container = gui_builder.set_texture("menu_board")
                                 .set_position(window_size.x / 2, window_size.y / 2 + 80)
                                 .set_origin(Origin::CENTER)
                                 .set_scale(4, 4)
                                 .make_container();

    sf::Rect<float> gui_container_bounds = m_gui_container->get_clickable_area();

    std::unique_ptr<SpriteElement> title_board = gui_builder.set_texture("title_board")
                                                            .set_position(window_size.x / 2, 150)
                                                            .set_scale(4, 4)
                                                            .set_origin(Origin::CENTER)
                                                            .make_sprite_element();

    std::unique_ptr<SpriteElement> title_board_paper = gui_builder.set_texture("paper_label")
                                                                  .set_position(window_size.x / 2, 150)
                                                                  .set_scale(4, 4)
                                                                  .set_origin(Origin::CENTER)
                                                                  .make_sprite_element();

    std::unique_ptr<TextElement> title_board_text = gui_builder.set_font("bulky_pixel")
                                                               .set_character_size(30)
                                                               .set_position(window_size.x / 2, 150)
                                                               .set_origin(Origin::CENTER)
                                                               .set_text_color(Colors::brown)
                                                               .set_text_string("Main Menu")
                                                               .make_text_element();

    std::unique_ptr<TextButton> play_button = gui_builder.set_texture("large_button")
                                                         .set_font("bulky_pixel")
                                                         .set_position(window_size.x / 2, gui_container_bounds.top + 125)
                                                         .set_origin(Origin::CENTER)
                                                         .set_scale(4, 4)
                                                         .set_scale_hover(4.2, 4.2)
                                                         .set_text_string("Play")
                                                         .set_character_size(30)
                                                         .set_character_size_hover(32)
                                                         .set_text_color(Colors::brown)
                                                         .set_text_offset(0, 0)
                                                         .set_callback([] () { puts("Play clicked"); })
                                                         .make_text_button();

    std::unique_ptr<TextButton> levels_button = gui_builder.set_texture("large_button")
                                                           .set_font("bulky_pixel")
                                                           .set_position(window_size.x / 2, gui_container_bounds.top + 255)
                                                           .set_origin(Origin::CENTER)
                                                           .set_scale(4, 4)
                                                           .set_scale_hover(4.2, 4.2)
                                                           .set_text_string("Levels")
                                                           .set_character_size(30)
                                                           .set_character_size_hover(32)
                                                           .set_text_color(Colors::brown)
                                                           .set_text_offset(0, 0)
                                                           .set_callback([] () { puts("Levels clicked"); })
                                                           .make_text_button();

    std::unique_ptr<TextButton> settings_button = gui_builder.set_texture("large_button")
                                                             .set_font("bulky_pixel")
                                                             .set_position(window_size.x / 2, gui_container_bounds.top + 385)
                                                             .set_origin(Origin::CENTER)
                                                             .set_scale(4, 4)
                                                             .set_scale_hover(4.2, 4.2)
                                                             .set_text_string("Settings")
                                                             .set_character_size(30)
                                                             .set_character_size_hover(32)
                                                             .set_text_color(Colors::brown)
                                                             .set_text_offset(0, 0)
                                                             .set_callback([] () { puts("Settings clicked"); })
                                                             .make_text_button();

    std::unique_ptr<TextButton> exit_button = gui_builder.set_texture("large_button")
                                                         .set_font("bulky_pixel")
                                                         .set_position(window_size.x / 2, gui_container_bounds.top + 515)
                                                         .set_origin(Origin::CENTER)
                                                         .set_scale(4, 4)
                                                         .set_scale_hover(4.2, 4.2)
                                                         .set_text_string("Exit")
                                                         .set_character_size(30)
                                                         .set_character_size_hover(32)
                                                         .set_text_color(Colors::brown)
                                                         .set_text_offset(0, 0)
                                                         .set_callback([] () { puts("Exit clicked"); })
                                                         .make_text_button();

    m_gui_container->push_back(std::move(title_board));
    m_gui_container->push_back(std::move(title_board_paper));
    m_gui_container->push_back(std::move(title_board_text));
    m_gui_container->push_back(std::move(play_button));
    m_gui_container->push_back(std::move(levels_button));
    m_gui_container->push_back(std::move(settings_button));
    m_gui_container->push_back(std::move(exit_button));
}
