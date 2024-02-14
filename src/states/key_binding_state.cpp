//
// Created by Gianni on 10/02/2024.
//

#include "key_binding_state.hpp"


KeyBindingState::KeyBindingState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
    , m_action(reinterpret_cast<std::string*>(user_ptr))
    , m_invalid_key_timer(-1)
{
    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

    m_invalid_key_text.setFont(m_context.font_manager->get("bulky_pixel"));
    m_invalid_key_text.setCharacterSize(32);
    m_invalid_key_text.setString("Invalid Key");
    m_invalid_key_text.setPosition(window_size.x / 2, 700);
    m_invalid_key_text.setFillColor(sf::Color::Transparent);
    utils::set_origin(m_invalid_key_text, Origin::CENTER);

    setup_gui();

    utils::gui::select_element(m_gui_container, m_context.window);
}

bool KeyBindingState::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Keyboard::Key selected_key = event.key.code;

        if (check_valid_key(selected_key))
        {
            m_context.settings->action_map[*m_action] = utils::key_to_string(selected_key);
            request_stack_pop();
            SoundPlayer::play_sound("key_binded");
        }
        else
        {
            m_invalid_key_text.setFillColor(sf::Color::Red);
            m_invalid_key_timer = 2;
        }
    }

    m_gui_container.handle_event(event);

    return false;
}

bool KeyBindingState::update(double dt)
{
    m_gui_container.update();

    m_invalid_key_text.setFillColor(m_invalid_key_timer > 0? sf::Color::Red : sf::Color::Transparent);

    m_invalid_key_timer -= dt;

    return true;
}

void KeyBindingState::on_world_draw()
{

}

void KeyBindingState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_gui_container);
    window.draw(m_invalid_key_text);
}

void KeyBindingState::setup_gui()
{
    static GUI_Builder gui_builder(m_context.texture_manager, m_context.font_manager);

    sf::Vector2f window_size = static_cast<sf::Vector2f>(m_context.window->getSize());

    std::unique_ptr<SpriteElement> message_board = gui_builder.set_texture("message_board")
            .set_position(window_size / 2.f)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .make_sprite_element();

    std::unique_ptr<SpriteElement> message_board_paper = gui_builder.set_texture("message_paper")
            .set_position(window_size / 2.f)
            .set_scale(4, 4)
            .set_origin(Origin::CENTER)
            .make_sprite_element();

    std::unique_ptr<TextElement> message_board_text = gui_builder.set_font("bulky_pixel")
            .set_character_size(30)
            .set_position(window_size / 2.f)
            .set_origin(Origin::CENTER)
            .set_text_color(Colors::brown)
            .set_text_string("Press Any Key")
            .make_text_element();

    std::unique_ptr<TextButton> back_button = gui_builder.set_texture("large_button")
            .set_font("bulky_pixel")
            .set_position(window_size.x - 150, window_size.y - 100)
            .set_origin(Origin::CENTER)
            .set_scale(4, 4)
            .set_scale_hover(4.2, 4.2)
            .set_text_string("Back")
            .set_character_size(30)
            .set_character_size_hover(32)
            .set_text_color(Colors::brown)
            .set_text_offset(0, 0)
            .set_callback([this] () { request_stack_pop(); })
            .make_text_button();

    m_gui_container.push_back(std::move(message_board));
    m_gui_container.push_back(std::move(message_board_paper));
    m_gui_container.push_back(std::move(message_board_text));
    m_gui_container.push_back(std::move(back_button));
}

bool KeyBindingState::check_valid_key(sf::Keyboard::Key key)
{
    for (const auto& [action, binding] : m_context.settings->action_map)
    {
        if (*m_action == action) continue;

        if (key == utils::string_to_key(binding))
            return false;
    }

    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
        return true;

    if (key >= sf::Keyboard::Left && key <= sf::Keyboard::Down)
        return true;

    if (key == sf::Keyboard::Space || key == sf::Keyboard::Enter)
        return true;

    return false;
}
