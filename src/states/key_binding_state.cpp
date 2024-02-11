//
// Created by Gianni on 10/02/2024.
//

#include "key_binding_state.hpp"


KeyBindingState::KeyBindingState(StateStack &state_stack, GameContext &context, UINT_PTR user_ptr)
    : State(state_stack, context)
    , m_gui_container(std::make_unique<GUI_Container>())
{
    setup_gui();
}

bool KeyBindingState::handle_events(const sf::Event &event)
{
    m_gui_container->handle_event(event);

    return false;
}

bool KeyBindingState::update(double dt)
{
    m_gui_container->update();

    return false;
}

void KeyBindingState::on_world_draw()
{

}

void KeyBindingState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(*m_gui_container);
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

    m_gui_container->push_back(std::move(message_board));
    m_gui_container->push_back(std::move(message_board_paper));
    m_gui_container->push_back(std::move(message_board_text));
}
