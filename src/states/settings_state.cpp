//
// Created by Gianni on 10/02/2024.
//

#include "settings_state.hpp"


SettingsState::SettingsState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
    build_gui();
}

void SettingsState::on_return()
{
    State::on_return();
}

bool SettingsState::handle_events(const sf::Event &event)
{
    return false;
}

bool SettingsState::update(double dt)
{
    return true;
}

void SettingsState::on_world_draw()
{
}

void SettingsState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    m_banner.draw(window);
    m_left_panel.draw(window);
}

void SettingsState::left_binding_callback()
{
    std::string* action = new std::string("move_left_action");

    auto action_ptr = reinterpret_cast<void*>(action);

    request_stack_push(StateID::KEY_BINDING, action_ptr);
}

void SettingsState::right_binding_callback()
{
    std::string* action = new std::string("move_right_action");

    auto action_ptr = reinterpret_cast<void*>(action);

    request_stack_push(StateID::KEY_BINDING, action_ptr);
}

void SettingsState::up_binding_callback()
{
    std::string* action = new std::string("jump_action");

    auto action_ptr = reinterpret_cast<void*>(action);

    request_stack_push(StateID::KEY_BINDING, action_ptr);
}

void SettingsState::back_callback()
{
    request_stack_pop();
}

void SettingsState::build_gui()
{

}
//
//void SettingsState::build_gui()
//{
//    const TextureManager& textures = *m_context.texture_manager;
//    const FontManager& fonts = *m_context.font_manager;
//
//    const auto [window_width, window_height] = static_cast<sf::Vector2f>(m_context.window->getSize());
//
//    { // banner
//        m_banner = GUI_Container(textures.get("title_board"));
//
//        GUI_Sprite* banner_paper = new GUI_Sprite(textures.get("paper_label"));
//        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Settings");
//
//        const auto [banner_width, banner_height] = m_banner.local_bb().getSize();
//        const auto [paper_width, paper_height] = banner_paper->local_bb().getSize();
//        const auto [text_width, text_height] = banner_text->local_bb().getSize();
//
//        m_banner.set_origin(banner_width / 2.f, banner_height / 2.f);
//        m_banner.set_scale(4.f);
//        m_banner.set_pos(window_width / 2.f, 150);
//
//        banner_paper->set_origin(paper_width / 2.f, paper_height / 2.f);
//        banner_paper->set_pos(banner_width / 2.f, banner_height / 2.f);
//
//        banner_text->set_origin(text_width / 2.f, text_height / 2.f);
//        banner_text->set_pos(banner_width / 2.f, banner_height / 2.f);
//        banner_text->set_scale(1.f / 4.f);
//
//        m_banner.pack(banner_paper);
//        m_banner.pack(banner_text);
//    }
//
//    { // left panel
//        m_left_panel = GUI_Container(textures.get("settings_board"));
//
//        GUI_Container* banner = new GUI_Container(textures.get("paper_label"));
//        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Audio");
//
////        GUI_Container* bg_paper = new GUI_Container(textures.get("settings_bg_paper"));
////        GUI_Text* music_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Music");
////        GUI_Text* sound_text = new GUI_Text(fonts.get("sound_text"), 30, "Sound");
////        GUI_Slider* music_slider = new GUI_Slider(textures.get("slider"), textures.get("slider_pointer"));
////        GUI_Slider* audi_slider = new GUI_Slider(textures.get("slider"), textures.get("slider_pointer"));
//
//        const auto [panel_width, panel_height] = m_left_panel.local_bb().getSize();
//        const auto [banner_width, banner_height] = banner->local_bb().getSize();
////        const auto [bg_paper_width, bg_paper_height] = bg_paper->local_bb().getSize();
//        const auto [b_text_width, b_text_height] = banner_text->local_bb().getSize();
////        const auto [m_text_width, m_text_height] = music_text->local_bb().getSize();
////        const auto [s_text_width, s_text_height] = sound_text->local_bb().getSize();
////        const auto [slider_width, slider_height] = music_slider->local_bb().getSize();
//
//        m_left_panel.set_origin(panel_width / 2.f, panel_height / 2.f);
//        m_left_panel.set_scale(4.f);
//        m_left_panel.set_pos(window_width / 3.5f, window_height / 2.f + 10.f);
//
//        banner->set_origin(banner_width / 2.f, banner_width / 2.f);
//        banner->set_pos(panel_width / 2.f, 100 / 4.f);
//        banner->pack(banner_text);
//
//        banner_text->set_origin(b_text_height / 2.f, b_text_height / 2.f);
////        banner_text->set_pos(banner_width / 2.f, banner_height / 2.f);
//        banner_text->set_scale(1.f / 4.f);
//
//        m_left_panel.pack(banner);
//    }
//
//}
