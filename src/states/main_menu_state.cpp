//
// Created by Gianni on 12/01/2024.
//

#include "main_menu_state.hpp"
#include "state_stack.hpp"

MainMenuState::MainMenuState(StateStack &state_stack, GameContext& context, void* user_ptr)
    : State(state_stack, context)
    , m_gui_container(std::make_unique<GUI_Container>())
{
    sf::Texture& bg_texture = m_context.texture_manager->get("blue");
    sf::Vector2i bg_size = static_cast<sf::Vector2i>(m_context.world_camera->get_size());

    m_scrolling_background = ScrollingBackground(bg_texture, bg_size);

    m_context.world_camera->set_center(m_context.world_camera->get_size() / 2.f);

    setup_gui();
}

void MainMenuState::on_exit()
{
    State::on_exit();

    for (auto& element : *m_gui_container)
        element->deselect();
}

void MainMenuState::on_return()
{
    State::on_return();

    for (auto& element : *m_gui_container)
    {
        if (element->get_clickable_area().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_context.window))))
        {
            element->select();
            break;
        }
    }
}

bool MainMenuState::handle_events(const sf::Event &event)
{
    m_gui_container->handle_event(event);

    return false;
}

bool MainMenuState::update(double dt)
{
    m_scrolling_background.update(dt);
    m_gui_container->update();

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

    if (m_status == Status::CURRENT)
    {
        window.draw(*m_gui_container);
    }
}

void MainMenuState::setup_gui()
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
                                                               .set_text_string("Main Menu")
                                                               .make_text_element();

    std::unique_ptr<SpriteElement> menu_board = gui_builder.set_texture("menu_board")
            .set_position(window_size.x / 2, window_size.y / 2 + 80)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .make_sprite_element();

    sf::Rect<float> menu_board_bounds = menu_board->get_clickable_area();

    std::unique_ptr<TextButton> play_button = gui_builder.set_texture("large_button")
                                                         .set_font("bulky_pixel")
                                                         .set_position(window_size.x / 2, menu_board_bounds.top + 125)
                                                         .set_origin(Origin::CENTER)
                                                         .set_scale(4, 4)
                                                         .set_scale_hover(4.2, 4.2)
                                                         .set_text_string("Play")
                                                         .set_character_size(30)
                                                         .set_character_size_hover(32)
                                                         .set_text_color(Colors::brown)
                                                         .set_text_offset(0, 0)
                                                         .set_callback([this] () {
                                                             LevelDetails* level_details = new LevelDetails {
                                                                     "../data/tmx/test_map3.tmj",
                                                                     "test_map3",
                                                                     "yellow"
                                                             };

                                                             auto level_details_ptr = reinterpret_cast<void*>(level_details);

                                                             request_stack_pop();
                                                             request_stack_push(StateID::GAME, level_details_ptr);
                                                         }).make_text_button();

    std::unique_ptr<TextButton> settings_button = gui_builder.set_texture("large_button")
                                                             .set_font("bulky_pixel")
                                                             .set_position(window_size.x / 2, menu_board_bounds.top + 255)
                                                             .set_origin(Origin::CENTER)
                                                             .set_scale(4, 4)
                                                             .set_scale_hover(4.2, 4.2)
                                                             .set_text_string("Settings")
                                                             .set_character_size(30)
                                                             .set_character_size_hover(32)
                                                             .set_text_color(Colors::brown)
                                                             .set_text_offset(0, 0)
                                                             .set_callback([this] () {
                                                                 request_stack_push(StateID::SETTINGS);
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
                                                         .set_callback([this] () {
                                                             request_stack_pop();
                                                         }).make_text_button();

    m_gui_container->push_back(std::move(title_board));
    m_gui_container->push_back(std::move(title_board_paper));
    m_gui_container->push_back(std::move(title_board_text));
    m_gui_container->push_back(std::move(menu_board));
    m_gui_container->push_back(std::move(play_button));
    m_gui_container->push_back(std::move(settings_button));
    m_gui_container->push_back(std::move(exit_button));
}

