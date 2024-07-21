//
// Created by Gianni on 10/02/2024.
//

#include "game_over_state.hpp"


GameOverState::GameOverState(StateStack &state_stack, GameContext &context, void* user_ptr)
    : State(state_stack, context)
{
    build_gui();

    sf::Vector2f gui_camera_pos = m_context.gui_camera->get_center();

    m_context.gui_camera->set_center(gui_camera_pos.x, gui_camera_pos.y + 1000);
    m_context.gui_camera->set_target(gui_camera_pos, easing_functions::linear);
}

bool GameOverState::handle_events(const sf::Event &event)
{
    if (m_context.gui_camera->target_reached())
        m_panel.handle_event(event);

    return false;
}

bool GameOverState::update(double dt)
{
    if (m_context.gui_camera->target_reached())
        m_panel.update();

    return true;
}

void GameOverState::on_world_draw()
{
}

void GameOverState::on_gui_draw()
{
    sf::RenderWindow& window = *m_context.window;

    m_banner.draw(window);
    m_panel.draw(window);
}

void GameOverState::restart_callback()
{
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new LoadWorld(m_context, StateID::GAME));
}

void GameOverState::main_menu_callback()
{
    request_stack_clear();
    request_stack_push(StateID::LOADING_STATE, new DoNothing(StateID::MAIN_MENU));
}

void GameOverState::exit_callback()
{
    request_stack_clear();
}

void GameOverState::build_gui()
{
    const TextureManager& textures = *m_context.texture_manager;
    const FontManager& fonts = *m_context.font_manager;

    const auto [win_width, win_height] = sf::Vector2f(m_context.window->getSize());

    { // banner
        m_banner = GUI_Container(textures.get("title_board"));

        GUI_Sprite* banner_paper = new GUI_Sprite(textures.get("paper_label"));
        GUI_Text* banner_text = new GUI_Text(fonts.get("bulky_pixel"), 30, "Game Over");

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

        GUI_Button* restart = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Restart");
        GUI_Button* main_manu = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Menu");
        GUI_Button* exit = new GUI_Button(textures.get("large_button"), fonts.get("bulky_pixel"), 30, "Exit");

        m_panel.set_origin(Origin::CENTER);
        m_panel.set_scale(4.f);
        m_panel.set_pos_glob(win_width / 2.f, win_height / 2.f + 80.f);

        m_panel.pack(restart);
        m_panel.pack(main_manu);
        m_panel.pack(exit);

        auto [width, height] = m_panel.bounding_box().getSize();

        restart->set_origin(Origin::CENTER);
        restart->set_scale(4.f);
        restart->set_pos_rel(width / 2.f, height * 0.25f);
        restart->set_callback([this](){restart_callback();});

        main_manu->set_origin(Origin::CENTER);
        main_manu->set_scale(4.f);
        main_manu->set_pos_rel(width / 2.f, height / 2.f);
        main_manu->set_callback([this](){main_menu_callback();});

        exit->set_origin(Origin::CENTER);
        exit->set_scale(4.f);
        exit->set_pos_rel(width / 2.f, height * 0.75f);
        exit->set_callback([this](){exit_callback();});
    }
}
