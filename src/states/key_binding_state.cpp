//
// Created by Gianni on 10/02/2024.
//

#include "key_binding_state.hpp"
#include "../asset_managers/font_manager.hpp"


KeyBindingState::KeyBindingState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
    , m_action(reinterpret_cast<std::string*>(user_ptr))
    , m_invalid_key_timer(-1)
{
    build_gui();
    m_invalid_key_text.setFont(m_context.font_manager->get("bulky_pixel"));
    m_invalid_key_text.setCharacterSize(32);
    m_invalid_key_text.setString("Invalid Key");
    m_invalid_key_text.setPosition(m_context.window->getSize().x / 2, 700);
    m_invalid_key_text.setFillColor(sf::Color::Transparent);
    utils::set_origin(m_invalid_key_text, Origin::CENTER);
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

    m_container.handle_event(event);

    return false;
}

bool KeyBindingState::update(double dt)
{
    m_invalid_key_text.setFillColor(m_invalid_key_timer > 0? sf::Color::Red : sf::Color::Transparent);
    m_invalid_key_timer -= dt;

    m_container.update();

    return true;
}

void KeyBindingState::on_world_draw()
{

}

void KeyBindingState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    m_container.draw(window);
    window.draw(m_invalid_key_text);
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

void KeyBindingState::back_callback()
{
    request_stack_pop();
}

void KeyBindingState::build_gui()
{
    const TextureManager& textures = *m_context.texture_manager;
    const FontManager& fonts = *m_context.font_manager;

    const auto [win_width, win_height] = sf::Vector2f(m_context.window->getSize());

    m_container = GUI_Container(textures.get("message_board"));

    GUI_Sprite* paper = new GUI_Sprite(textures.get("message_paper"));
    GUI_Text* text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Press Any Key");
    GUI_Button* back = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Back");

    m_container.pack(paper);
    m_container.pack(text);
    m_container.pack(back);

    m_container.set_origin(Origin::CENTER);
    m_container.set_scale(4.f);
    m_container.set_pos_glob(win_width / 2.f, win_height / 2.f);

    const auto [width, height] = m_container.bounding_box().getSize();

    paper->set_origin(Origin::CENTER);
    paper->set_scale(4.f);
    paper->set_pos_rel(width / 2.f, height / 2.f);

    text->set_origin(Origin::CENTER);
    text->set_pos_rel(width / 2.f, height / 2.f);

    back->set_origin(Origin::CENTER);
    back->set_scale(4.f);
    back->set_pos_glob(win_width - 150.f, win_height - 100.f);
    back->set_callback([this](){back_callback();});
}
