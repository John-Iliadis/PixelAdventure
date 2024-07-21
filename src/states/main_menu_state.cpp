//
// Created by Gianni on 12/01/2024.
//

#include "main_menu_state.hpp"


MainMenuState::MainMenuState(StateStack &state_stack, GameContext& context, void* user_ptr)
    : State(state_stack, context)
    , m_scrolling_background(m_context.texture_manager->get("blue"), static_cast<sf::Vector2i>(m_context.world_camera->get_size()))
{
    build_gui();
    m_context.world_camera->set_center(m_context.world_camera->get_size() / 2.f); // todo: delete this
    MusicPlayer::play("menu_music", true);
}

void MainMenuState::on_exit()
{
    State::on_exit();
}

void MainMenuState::on_return()
{
    State::on_return();
    m_panel.on_return(Cursor::get_mouse_pos());
}

bool MainMenuState::handle_events(const sf::Event &event)
{
    m_panel.handle_event(event);

    return false;
}

bool MainMenuState::update(double dt)
{
    m_scrolling_background.update(dt);

    if (m_status == Status::CURRENT)
        m_panel.update();

    return false;
}

void MainMenuState::on_world_draw()
{
    sf::RenderWindow& window = *m_context.window;

    window.draw(m_scrolling_background);
}

void MainMenuState::on_gui_draw()
{
    if (m_status == Status::CURRENT)
    {
        sf::RenderWindow& window = *m_context.window;

        m_banner.draw(window);
        m_panel.draw(window);
    }
}

void MainMenuState::play_callback()
{
    MusicPlayer::stop();
    request_stack_pop();
    request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
}

void MainMenuState::settings_callback()
{
    request_stack_push(StateID::SETTINGS);
}

void MainMenuState::exit_callback()
{
    request_stack_clear();
}

void MainMenuState::build_gui()
{
    const TextureManager& textures = *m_context.texture_manager;
    const FontManager& fonts = *m_context.font_manager;

    const auto [win_width, win_height] = sf::Vector2f(m_context.window->getSize());

    { // banner
        m_banner = GUI_Container(textures.get("title_board"));

        GUI_Sprite* banner_paper = new GUI_Sprite(textures.get("paper_label"));
        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Main Menu");

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

    { // panel
        m_panel = GUI_Container(textures.get("menu_board"));

        GUI_Button* play = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Play");
        GUI_Button* settings = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Settings");
        GUI_Button* exit = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Exit");

        m_panel.set_origin(Origin::CENTER);
        m_panel.set_scale(4.f);
        m_panel.set_pos_glob(win_width / 2.f, win_height / 2.f + 80.f);

        m_panel.pack(play);
        m_panel.pack(settings);
        m_panel.pack(exit);

        auto [width, height] = m_panel.bounding_box().getSize();

        play->set_origin(Origin::CENTER);
        play->set_scale(4.f);
        play->set_pos_rel(width / 2.f, height * 0.25f);
        play->set_callback([this](){play_callback();});

        settings->set_origin(Origin::CENTER);
        settings->set_scale(4.f);
        settings->set_pos_rel(width / 2.f, height / 2.f);
        settings->set_callback([this](){settings_callback();});

        exit->set_origin(Origin::CENTER);
        exit->set_scale(4.f);
        exit->set_pos_rel(width / 2.f, height * 0.75f);
        exit->set_callback([this](){exit_callback();});
    }
}
