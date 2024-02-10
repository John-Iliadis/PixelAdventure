//
// Created by Gianni on 10/02/2024.
//

#include <iostream>
#include "settings_state.hpp"



SettingsState::SettingsState(StateStack &state_stack, GameContext &context, UINT_PTR user_ptr)
    : State(state_stack, context)
    , m_gui_container(std::make_unique<GUI_Container>())
{
    setup_gui();

    place_holder_1 = 10;
    place_holder_2 = 10;
}

bool SettingsState::handle_events(const sf::Event &event)
{
    m_gui_container->handle_event(event);

    return false;
}

bool SettingsState::update(double dt)
{
    m_gui_container->update(sf::Mouse::getPosition(*m_context.window));
    return false;
}

void SettingsState::on_world_draw()
{
}

void SettingsState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(*m_gui_container);
}

void SettingsState::setup_gui()
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
                                                               .set_text_color(sf::Color::Black)
                                                               .set_text_string("Settings")
                                                               .make_text_element();
    /* audio board */
    std::unique_ptr<SpriteElement> audio_board = gui_builder.set_texture("settings_board")
                                                            .set_position(int(window_size.x / 3.5), window_size.y / 2 + 80)
                                                            .set_scale(4, 4)
                                                            .set_origin(Origin::CENTER)
                                                            .make_sprite_element();

    sf::Rect<float> audio_board_bounds = audio_board->get_clickable_area();

    std::unique_ptr<SpriteElement> audio_board_title_paper = gui_builder.set_texture("paper_label")
            .set_position(audio_board_bounds.left + audio_board_bounds.width / 2, audio_board_bounds.top + 100)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .make_sprite_element();

    std::unique_ptr<TextElement> audio_board_title_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(audio_board_title_paper->get_position())
            .set_origin(Origin::CENTER)
            .set_text_color(sf::Color::Black)
            .set_text_string("Audio")
            .make_text_element();

    std::unique_ptr<SpriteElement> audio_board_background_paper = gui_builder.set_texture("settings_bg_paper")
            .set_position(audio_board->get_position().x, 658)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .make_sprite_element();

    sf::Rect<float> audio_paper_bounds = audio_board_background_paper->get_clickable_area();

    std::unique_ptr<TextElement> music_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(audio_paper_bounds.left + 90, audio_paper_bounds.top + 140)
            .set_origin(Origin::CENTER_LEFT)
            .set_text_color(sf::Color::Black)
            .set_text_string("Music:")
            .make_text_element();

    std::unique_ptr<Slider> music_slider = gui_builder.set_position(audio_paper_bounds.left + 420, audio_paper_bounds.top + 140)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .set_slider_value(&place_holder_1)
            .set_slider_min(0)
            .set_slider_max(100)
            .make_slider();

    std::unique_ptr<TextElement> sound_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(audio_paper_bounds.left + 90, audio_paper_bounds.top + audio_paper_bounds.height - 140)
            .set_origin(Origin::CENTER_LEFT)
            .set_text_color(sf::Color::Black)
            .set_text_string("Sound:")
            .make_text_element();

    std::unique_ptr<Slider> sound_slider = gui_builder.set_position(audio_paper_bounds.left + 420, audio_paper_bounds.top + audio_paper_bounds.height - 140)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .set_slider_value(&place_holder_2)
            .set_slider_min(0)
            .set_slider_max(100)
            .make_slider();

    /* key binding board */
    std::unique_ptr<SpriteElement> key_binding_board = gui_builder.set_texture("settings_board")
                                                                  .set_position(int(window_size.x - window_size.x / 3.5), window_size.y / 2 + 80)
                                                                  .set_scale(4, 4)
                                                                  .set_origin(Origin::CENTER)
                                                                  .make_sprite_element();

    sf::Rect<float> key_binding_board_bounds = key_binding_board->get_clickable_area();

    std::unique_ptr<SpriteElement> key_binding_board_title_paper = gui_builder.set_texture("paper_label")
                                                                              .set_position(key_binding_board_bounds.left + key_binding_board_bounds.width / 2, key_binding_board_bounds.top + 100)
                                                                              .set_scale(4, 4)
                                                                              .set_origin(Origin::CENTER)
                                                                              .make_sprite_element();

    std::unique_ptr<TextElement> key_binding_board_title_text = gui_builder.set_font("bulky_pixel")
                                                                           .set_character_size(30)
                                                                           .set_position(key_binding_board_title_paper->get_position())
                                                                           .set_origin(Origin::CENTER)
                                                                           .set_text_color(sf::Color::Black)
                                                                           .set_text_string("Keys")
                                                                           .make_text_element();

    std::unique_ptr<SpriteElement> key_binding_board_background_paper = gui_builder.set_texture("settings_bg_paper")
                                                                                   .set_position(key_binding_board->get_position().x, 658)
                                                                                   .set_scale(4, 4)
                                                                                   .set_origin(Origin::CENTER)
                                                                                   .make_sprite_element();

    sf::Rect<float> key_binding_paper_bounds = key_binding_board_background_paper->get_clickable_area();

    std::unique_ptr<TextElement> left_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(key_binding_paper_bounds.left + 90, key_binding_paper_bounds.top + 120)
            .set_origin(Origin::CENTER_LEFT)
            .set_text_color(sf::Color::Black)
            .set_text_string("Left:")
            .make_text_element();

    std::unique_ptr<TextElement> right_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(key_binding_paper_bounds.left + 90, key_binding_board_background_paper->get_position().y)
            .set_origin(Origin::CENTER_LEFT)
            .set_text_color(sf::Color::Black)
            .set_text_string("Right:")
            .make_text_element();

    std::unique_ptr<TextElement> jump_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(key_binding_paper_bounds.left + 90, key_binding_paper_bounds.top + key_binding_paper_bounds.height - 120)
            .set_origin(Origin::CENTER_LEFT)
            .set_text_color(sf::Color::Black)
            .set_text_string("Jump:")
            .make_text_element();

    std::unique_ptr<TextButton> left_button = gui_builder.set_texture("small_button")
            .set_font("bulky_pixel")
            .set_position(key_binding_paper_bounds.left + 420, key_binding_paper_bounds.top + 120)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Left")
            .set_character_size(20)
            .set_character_size_hover(22)
            .set_text_color(sf::Color::Black)
            .set_text_offset(0, -3)
            .set_callback([] () { puts("Left button clicked"); })
            .make_text_button();

    std::unique_ptr<TextButton> right_button = gui_builder.set_texture("small_button")
            .set_font("bulky_pixel")
            .set_position(key_binding_paper_bounds.left + 420, key_binding_board_background_paper->get_position().y)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Right")
            .set_character_size(20)
            .set_character_size_hover(22)
            .set_text_color(sf::Color::Black)
            .set_text_offset(0, -3)
            .set_callback([] () { puts("Right button clicked"); })
            .make_text_button();

    std::unique_ptr<TextButton> jump_button = gui_builder.set_texture("small_button")
            .set_font("bulky_pixel")
            .set_position(key_binding_paper_bounds.left + 420, key_binding_paper_bounds.top + key_binding_paper_bounds.height - 120)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Jump")
            .set_character_size(20)
            .set_character_size_hover(22)
            .set_text_color(sf::Color::Black)
            .set_text_offset(0, -3)
            .set_callback([] () { puts("Jump button clicked"); })
            .make_text_button();

    std::unique_ptr<TextButton> back_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(window_size.x - 150, window_size.y - 100)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Back")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(sf::Color::Black)
            .set_text_offset(0, 0)
            .set_callback([] () { puts("Back button clicked"); })
            .make_text_button();

    m_gui_container->push_back(std::move(title_board));
    m_gui_container->push_back(std::move(title_board_paper));
    m_gui_container->push_back(std::move(title_board_text));
    m_gui_container->push_back(std::move(audio_board));
    m_gui_container->push_back(std::move(key_binding_board));
    m_gui_container->push_back(std::move(audio_board_title_paper));
    m_gui_container->push_back(std::move(key_binding_board_title_paper));
    m_gui_container->push_back(std::move(audio_board_title_text));
    m_gui_container->push_back(std::move(key_binding_board_title_text));
    m_gui_container->push_back(std::move(audio_board_background_paper));
    m_gui_container->push_back(std::move(key_binding_board_background_paper));
    m_gui_container->push_back(std::move(music_text));
    m_gui_container->push_back(std::move(music_slider));
    m_gui_container->push_back(std::move(sound_text));
    m_gui_container->push_back(std::move(sound_slider));
    m_gui_container->push_back(std::move(left_text));
    m_gui_container->push_back(std::move(right_text));
    m_gui_container->push_back(std::move(jump_text));
    m_gui_container->push_back(std::move(left_button));
    m_gui_container->push_back(std::move(right_button));
    m_gui_container->push_back(std::move(jump_button));
    m_gui_container->push_back(std::move(back_button));
}
