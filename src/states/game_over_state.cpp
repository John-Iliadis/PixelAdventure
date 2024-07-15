//
// Created by Gianni on 10/02/2024.
//

#include "game_over_state.hpp"


GameOverState::GameOverState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
    setup_gui();

    sf::Vector2f gui_camera_pos = m_context.gui_camera->get_center();
    m_context.gui_camera->set_center(gui_camera_pos.x, gui_camera_pos.y + 1000);
    m_context.gui_camera->set_target(gui_camera_pos, easing_functions::linear);
}

bool GameOverState::handle_events(const sf::Event &event)
{
    if (m_context.gui_camera->target_reached())
        m_gui_container.handle_event(event);

    return false;
}

bool GameOverState::update(double dt)
{
    if (m_context.gui_camera->target_reached())
        m_gui_container.update(m_context.window);

    return true;
}

void GameOverState::on_world_draw()
{

}

void GameOverState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_gui_container);
}

void GameOverState::setup_gui()
{
    static GUI_Builder gui_builder(m_context.texture_manager, m_context.font_manager);

    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

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
            .set_text_string("Game Over")
            .make_text_element();

    std::unique_ptr<SpriteElement> game_over_board = gui_builder.set_texture("menu_board")
            .set_position(window_size.x / 2, window_size.y / 2 + 80)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .make_sprite_element();

    sf::Rect<float> menu_board_bounds = game_over_board->get_clickable_area();

    std::unique_ptr<TextButton> restart_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(window_size.x / 2, menu_board_bounds.top + 125)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Restart")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([this] () {
                m_gui_container.deselect_all();

                request_stack_clear();
                request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
            }).make_text_button();

    std::unique_ptr<TextButton> main_menu_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(window_size.x / 2, menu_board_bounds.top + 255)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Menu")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([this] () {
                m_gui_container.deselect_all();

                request_stack_clear();
                request_stack_push(StateID::LOADING_STATE, new DoNothing(StateID::MAIN_MENU));
            }).make_text_button();

    std::unique_ptr<TextButton> exit_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(window_size.x / 2, menu_board_bounds.top + 385)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Exit")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([this] () { request_stack_clear(); })
            .make_text_button();

    m_gui_container.push_back(std::move(title_board));
    m_gui_container.push_back(std::move(title_board_paper));
    m_gui_container.push_back(std::move(title_board_text));
    m_gui_container.push_back(std::move(game_over_board));
    m_gui_container.push_back(std::move(restart_button));
    m_gui_container.push_back(std::move(main_menu_button));
    m_gui_container.push_back(std::move(exit_button));
}

