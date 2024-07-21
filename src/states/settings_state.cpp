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
    build_gui();
    m_right_panel.on_return(Cursor::get_mouse_pos());
    m_left_panel.on_return(Cursor::get_mouse_pos());
}

bool SettingsState::handle_events(const sf::Event &event)
{
    m_left_panel.handle_event(event);
    m_right_panel.handle_event(event);

    return false;
}

bool SettingsState::update(double dt)
{
    if (m_status == Status::CURRENT)
    {
        m_left_panel.update();
        m_right_panel.update();
    }

    return true;
}

void SettingsState::on_world_draw()
{
}

void SettingsState::on_gui_draw()
{
    if (m_status == Status::CURRENT)
    {
        sf::RenderWindow& window = *m_context.window;

        m_banner.draw(window);
        m_left_panel.draw(window);
        m_right_panel.draw(window);
    }
}

void SettingsState::left_binding_callback()
{
    std::string* action = new std::string("move_left_action");

    request_stack_push(StateID::KEY_BINDING, action);
}

void SettingsState::right_binding_callback()
{
    std::string* action = new std::string("move_right_action");

    request_stack_push(StateID::KEY_BINDING, action);
}

void SettingsState::up_binding_callback()
{
    std::string* action = new std::string("jump_action");

    request_stack_push(StateID::KEY_BINDING, action);
}

void SettingsState::back_callback()
{
    request_stack_pop();
}

void SettingsState::build_gui()
{
    const TextureManager& textures = *m_context.texture_manager;
    const FontManager& fonts = *m_context.font_manager;

    const auto [win_width, win_height] = sf::Vector2f(m_context.window->getSize());

    { // banner
        m_banner = GUI_Container(textures.get("title_board"));

        GUI_Sprite* banner_paper = new GUI_Sprite(textures.get("paper_label"));
        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Settings");

        m_banner.pack(banner_paper);
        m_banner.pack(banner_text);

        m_banner.set_origin(Origin::CENTER);
        m_banner.set_scale(4.f);
        m_banner.set_pos_glob(win_width / 2.f, 150.f);

        sf::Vector2f banner_center
        {
            m_banner.bounding_box().left + m_banner.bounding_box().width / 2.f,
            m_banner.bounding_box().top + m_banner.bounding_box().height / 2.f
        };

        banner_paper->set_origin(Origin::CENTER);
        banner_paper->set_pos_glob(banner_center.x, banner_center.y);
        banner_paper->set_scale(4.f);

        banner_text->set_origin(Origin::CENTER);
        banner_text->set_pos_glob(banner_center.x, banner_center.y);
    }

    { // left panel
        m_left_panel = GUI_Container(textures.get("settings_board"));

        GUI_Container* banner = new GUI_Container(textures.get("paper_label"));
        GUI_Container* inner_panel = new GUI_Container(textures.get("settings_bg_paper"));
        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Audio");
        GUI_Text* music_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Music:");
        GUI_Text* sound_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Sound:");
        GUI_Slider* music_slider = new GUI_Slider(textures.get("slider"), textures.get("slider_pointer"));
        GUI_Slider* sound_slider = new GUI_Slider(textures.get("slider"), textures.get("slider_pointer"));

        m_left_panel.pack(banner);
        m_left_panel.pack(inner_panel);
        banner->pack(banner_text);
        inner_panel->pack(music_text);
        inner_panel->pack(sound_text);
        inner_panel->pack(music_slider);
        inner_panel->pack(sound_slider);

        m_left_panel.set_origin(Origin::CENTER);
        m_left_panel.set_scale(4.f);
        m_left_panel.set_pos_glob(win_width * 0.3f, win_height / 2.f + 80.f);
        sf::FloatRect panel_bb = m_left_panel.bounding_box();

        { // banner
            banner->set_origin(Origin::CENTER);
            banner->set_scale(4.f);
            banner->set_pos_rel(panel_bb.width * 0.5f, 100.f);

            const auto [width, height] = banner->bounding_box().getSize();

            banner_text->set_origin(Origin::CENTER);
            banner_text->set_pos_rel(width / 2.f, height / 2.f);
        }

        { // inner panel
            inner_panel->set_origin(Origin::CENTER);
            inner_panel->set_scale(4.f);
            inner_panel->set_pos_rel(panel_bb.width * 0.5f, 294.f);

            const auto [width, height] = inner_panel->bounding_box().getSize();

            music_text->set_origin(Origin::CENTER_LEFT);
            music_text->set_pos_rel(100.f, height * 0.35);

            sound_text->set_origin(Origin::CENTER_LEFT);
            sound_text->set_pos_rel(100.f, height * 0.65f);

            music_slider->set_value(&m_context.settings->music_volume, 0.f, 100.f);
            music_slider->set_origin(Origin::CENTER);
            music_slider->set_scale(4.f);
            music_slider->set_pos_rel(400.f, height * 0.35f);

            sound_slider->set_value(&m_context.settings->sound_volume, 0.f, 100.f);
            sound_slider->set_origin(Origin::CENTER);
            sound_slider->set_scale(4.f);
            sound_slider->set_pos_rel(400.f, height * 0.65f);
        }
    }

    { // right panel
        m_right_panel = GUI_Container(textures.get("settings_board"));

        GUI_Container* banner = new GUI_Container(textures.get("paper_label"));
        GUI_Container* inner_panel = new GUI_Container(textures.get("settings_bg_paper"));
        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Keys");
        GUI_Text* left_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Left");
        GUI_Text* right_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Right:");
        GUI_Text* jump_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Jump:");
        GUI_Button* left_button = new GUI_Button(textures.get("small_button"), fonts.get("bulky_pixel"), 20);
        GUI_Button* right_button = new GUI_Button(textures.get("small_button"), fonts.get("bulky_pixel"), 20);
        GUI_Button* jump_button = new GUI_Button(textures.get("small_button"), fonts.get("bulky_pixel"), 20);
        GUI_Button* back_button = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Back");

        m_right_panel.pack(banner);
        m_right_panel.pack(inner_panel);
        banner->pack(banner_text);
        inner_panel->pack(left_text);
        inner_panel->pack(right_text);
        inner_panel->pack(jump_text);
        inner_panel->pack(left_button);
        inner_panel->pack(right_button);
        inner_panel->pack(jump_button);
        inner_panel->pack(back_button);

        m_right_panel.set_origin(Origin::CENTER);
        m_right_panel.set_scale(4.f);
        m_right_panel.set_pos_glob(win_width * 0.7f, win_height /2.f + 80.f);
        sf::FloatRect panel_bb = m_right_panel.bounding_box();

        { // banner
            banner->set_origin(Origin::CENTER);
            banner->set_scale(4.f);
            banner->set_pos_rel(panel_bb.width * 0.5f, 100.f);

            const auto [width, height] = banner->bounding_box().getSize();

            banner_text->set_origin(Origin::CENTER);
            banner_text->set_pos_rel(width / 2.f, height / 2.f);
        }

        { // inner panel
            inner_panel->set_origin(Origin::CENTER);
            inner_panel->set_scale(4.f);
            inner_panel->set_pos_rel(panel_bb.width * 0.5f, 294.f);

            const auto [width, height] = inner_panel->bounding_box().getSize();

            left_text->set_origin(Origin::CENTER_LEFT);
            left_text->set_pos_rel(100.f, height * 0.3f);

            right_text->set_origin(Origin::CENTER_LEFT);
            right_text->set_pos_rel(100.f, height * 0.5f);

            jump_text->set_origin(Origin::CENTER_LEFT);
            jump_text->set_pos_rel(100.f, height * 0.7f);

            left_button->set_origin(Origin::CENTER);
            left_button->set_scale(4.f);
            left_button->set_pos_rel(420.f, height * 0.3f);
            left_button->set_text_offset(0.f, -2.f);
            left_button->set_string(m_context.settings->action_map["move_left_action"]);
            left_button->set_callback([this](){left_binding_callback();});

            right_button->set_origin(Origin::CENTER);
            right_button->set_scale(4.f);
            right_button->set_pos_rel(420.f, height * 0.5f);
            right_button->set_text_offset(0.f, -2.f);
            right_button->set_string(m_context.settings->action_map["move_right_action"]);
            right_button->set_callback([this](){right_binding_callback();});

            jump_button->set_origin(Origin::CENTER);
            jump_button->set_scale(4.f);
            jump_button->set_pos_rel(420.f, height * 0.7f);
            jump_button->set_text_offset(0.f, -2.f);
            jump_button->set_string(m_context.settings->action_map["jump_action"]);
            jump_button->set_callback([this](){up_binding_callback();});

            back_button->set_origin(Origin::CENTER);
            back_button->set_scale(4.f);
            back_button->set_pos_glob(win_width - 150.f, win_height - 100.f);
            back_button->set_callback([this](){back_callback();});
        }
    }
}
