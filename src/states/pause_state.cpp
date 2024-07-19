//
// Created by Gianni on 10/02/2024.
//

#include "pause_state.hpp"


PauseState::PauseState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
    build_gui();

    m_dark_overlay.setSize(static_cast<sf::Vector2f>(m_context.window->getSize()));
    m_dark_overlay.setFillColor(sf::Color(0, 0, 0, 128));

    SoundPlayer::play_sound("window_open");
}

void PauseState::on_exit()
{
    State::on_exit();
}

void PauseState::on_return()
{
    State::on_return();
}

bool PauseState::handle_events(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            request_stack_pop();
        }
    }

    m_top_panel.handle_event(event);
    m_bottom_panel.handle_event(event);

    return false;
}

bool PauseState::update(double dt)
{
    return false;
}

void PauseState::on_world_draw()
{
}

void PauseState::on_gui_draw()
{
    sf::RenderWindow &window = *m_context.window;

    window.draw(m_dark_overlay);

    if (m_status == Status::CURRENT)
    {
        m_banner.draw(window);
        m_top_panel.draw(window);
        m_bottom_panel.draw(window);
    }
}

void PauseState::play_callback()
{
    request_stack_pop();
}

void PauseState::restart_callback()
{
    MusicPlayer::stop();
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
}

void PauseState::settings_callback()
{
    request_stack_push(StateID::SETTINGS);
}

void PauseState::menu_callback()
{
    MusicPlayer::stop();
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new DoNothing(StateID::MAIN_MENU));
}

void PauseState::desktop_callback()
{
    request_stack_clear();
}

void PauseState::build_gui()
{
    const TextureManager& textures = *m_context.texture_manager;
    const FontManager& fonts = *m_context.font_manager;

    const auto [win_width, win_height] = sf::Vector2f(m_context.window->getSize());

    { // banner
        m_banner = GUI_Container(textures.get("title_board"));

        GUI_Sprite* banner_paper = new GUI_Sprite(textures.get("paper_label"));
        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Pause");

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

    { // top panel
        m_top_panel = GUI_Container(textures.get("pause_board_top"));

        GUI_Button* play = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Play");
        GUI_Button* restart = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Restart");
        GUI_Button* settings = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Settings");

        m_top_panel.pack(play);
        m_top_panel.pack(restart);
        m_top_panel.pack(settings);

        m_top_panel.set_origin(Origin::CENTER_TOP);
        m_top_panel.set_scale(4.f);
        m_top_panel.set_pos_glob(win_width / 2.f, 250.f);

        auto const [width, height] = m_top_panel.bounding_box().getSize();

        play->set_origin(Origin::CENTER);
        play->set_scale(4.f);
        play->set_pos_rel(width / 2.f, height * 0.25f);
        play->set_callback([this](){play_callback();});

        restart->set_origin(Origin::CENTER);
        restart->set_scale(4.f);
        restart->set_pos_rel(width / 2.f, height * 0.5f);
        restart->set_callback([this](){restart_callback();});

        settings->set_origin(Origin::CENTER);
        settings->set_scale(4.f);
        settings->set_pos_rel(width / 2.f, height * 0.75f);
        settings->set_callback([this](){settings_callback();});
    }

    { // bottom panel
        m_bottom_panel = GUI_Container(textures.get("pause_board_bottom"));

        GUI_Button* menu = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Menu");
        GUI_Button* desktop = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Desktop");

        m_bottom_panel.pack(menu);
        m_bottom_panel.pack(desktop);

        m_bottom_panel.set_origin(Origin::CENTER);
        m_bottom_panel.set_scale(4.f);
        m_bottom_panel.set_pos_glob(win_width / 2.f, 900.f);

        auto const [width, height] = m_bottom_panel.bounding_box().getSize();

        menu->set_origin(Origin::CENTER);
        menu->set_scale(4.f);
        menu->set_pos_rel(width * 0.3f, height * 0.5f);
        menu->set_callback([this](){menu_callback();});

        desktop->set_origin(Origin::CENTER);
        desktop->set_scale(4.f);
        desktop->set_pos_rel(width * 0.7f, height * 0.5f);
        desktop->set_callback([this](){desktop_callback();});
    }
}
