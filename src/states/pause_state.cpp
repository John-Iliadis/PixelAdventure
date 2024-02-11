//
// Created by Gianni on 10/02/2024.
//

#include "pause_state.hpp"


PauseState::PauseState(StateStack &state_stack, GameContext &context, UINT_PTR user_ptr)
    : State(state_stack, context)
    , m_gui_container(std::make_unique<GUI_Container>())
{
    setup_gui();
}

bool PauseState::handle_events(const sf::Event &event)
{
    m_gui_container->handle_event(event);

    return false;
}

bool PauseState::update(double dt)
{
    m_gui_container->update();

    return false;
}

void PauseState::on_world_draw()
{
}

void PauseState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(*m_gui_container);
}

void PauseState::setup_gui()
{
    static GUI_Builder gui_builder(m_context.texture_manager, m_context.font_manager);

    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

    /* title */
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
            .set_text_string("Pause")
            .make_text_element();

    /* top board */
    std::unique_ptr<SpriteElement> top_board = gui_builder.set_texture("pause_board_top")
            .set_position(window_size.x / 2, 250)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER_TOP)
            .make_sprite_element();

    sf::Rect<float> top_board_bounds = top_board->get_clickable_area();

    std::unique_ptr<TextButton> play_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(top_board->get_position().x, top_board_bounds.top + 125)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Play")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([] () { puts("Play button clicked"); })
            .make_text_button();

    std::unique_ptr<TextButton> restart_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(top_board->get_position().x, top_board_bounds.top + 255)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Restart")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([] () { puts("Restart button clicked"); })
            .make_text_button();

    std::unique_ptr<TextButton> settings_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(top_board->get_position().x, top_board_bounds.top + 385)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Settings")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([] () { puts("Settings button clicked"); })
            .make_text_button();

    /* bottom board */
    std::unique_ptr<SpriteElement> bottom_board = gui_builder.set_texture("pause_board_bottom")
            .set_position(window_size.x / 2, 900)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .make_sprite_element();

    sf::Rect<float> bottom_board_bounds = bottom_board->get_clickable_area();

    std::unique_ptr<TextButton> main_menu_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(bottom_board_bounds.left + 190, bottom_board->get_position().y)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Menu")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([] () { puts("Main menu button clicked"); })
            .make_text_button();

    std::unique_ptr<TextButton> desktop_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(bottom_board_bounds.left + bottom_board_bounds.width - 190, bottom_board->get_position().y)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Desktop")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([] () { puts("Desktop button clicked"); })
            .make_text_button();

    m_gui_container->push_back(std::move(title_board));
    m_gui_container->push_back(std::move(title_board_paper));
    m_gui_container->push_back(std::move(title_board_text));
    m_gui_container->push_back(std::move(top_board));
    m_gui_container->push_back(std::move(bottom_board));
    m_gui_container->push_back(std::move(play_button));
    m_gui_container->push_back(std::move(restart_button));
    m_gui_container->push_back(std::move(settings_button));
    m_gui_container->push_back(std::move(main_menu_button));
    m_gui_container->push_back(std::move(desktop_button));
}
