cmake_minimum_required(VERSION 3.27)
project(Pixel_Adventure)

set(CMAKE_CXX_STANDARD 23)

add_executable(Pixel_Adventure
        src/main.cpp
        src/game.cpp
        src/game.hpp
        src/utilities/utils.hpp
        src/utilities/utils.cpp
        src/asset_managers/asset_manager.hpp
        src/asset_managers/asset_manager.inl
        src/asset_managers/texture_manager.hpp
        src/asset_managers/font_manager.hpp
        src/asset_managers/sound_buffer_manager.hpp
        src/asset_managers/music_manager.hpp
        src/enums/state_identifiers.hpp
        src/states/state.cpp
        src/states/state.hpp
        src/states/game_context.hpp
        src/states/state_stack.cpp
        src/states/state_stack.hpp
        src/states/state_factory.cpp
        src/states/state_factory.hpp
        src/states/main_menu_state.cpp
        src/states/main_menu_state.hpp
        src/states/game_state.cpp
        src/states/game_state.hpp
        src/world/world.cpp
        src/world/world.hpp
        src/world/player/player.cpp
        src/world/player/player.hpp
        src/scrolling_background/scrolling_background.cpp
        src/scrolling_background/scrolling_background.hpp
        src/vendor/json.hpp
        src/world/collision.cpp
        src/world/collision.hpp
        src/animation/sprite_sheet.cpp
        src/animation/sprite_sheet.hpp
        src/world/player/player_state.hpp
        src/world/player/idle_state.cpp
        src/world/player/idle_state.hpp
        src/world/player/running_state.cpp
        src/world/player/running_state.hpp
        src/world/player/jumping_state.cpp
        src/world/player/jumping_state.hpp
        src/world/player/falling_state.cpp
        src/world/player/falling_state.hpp
        src/world/player/wall_sliding_state.cpp
        src/world/player/wall_sliding_state.hpp
        src/world/player/double_jumping_state.cpp
        src/world/player/double_jumping_state.hpp
        src/world/sprite_collider.cpp
        src/world/sprite_collider.hpp
        src/animation/animation_manager.cpp
        src/animation/animation_manager.hpp
        src/structs/player_data.hpp
        src/world/movable_object.cpp
        src/world/movable_object.hpp
        src/world/tiled_json_loader.cpp
        src/world/tiled_json_loader.hpp
        src/structs/map_data.hpp
        src/world/traps/spikes/spike.cpp
        src/world/traps/spikes/spike.hpp
        src/camera/camera.cpp
        src/camera/camera.hpp
        src/world/checkpoint/checkpoint.cpp
        src/world/checkpoint/checkpoint.hpp
        src/world/checkpoint/checkpoint_manager.cpp
        src/world/checkpoint/checkpoint_manager.hpp
        src/world/particles/death_particle.cpp
        src/world/particles/death_particle.hpp
        src/world/particles/death_particle_system.cpp
        src/world/particles/death_particle_system.hpp
        src/animation/animation.cpp
        src/animation/animation.hpp
        src/animation/animation_interface.hpp
        src/world/player/respawning_state.cpp
        src/world/player/respawning_state.hpp
        src/world/traps/fire_trap/fire_trap.cpp
        src/world/traps/fire_trap/fire_trap.hpp
        src/world/tiled_json_loader.inl
        src/world/traps/saw/saw.cpp
        src/world/traps/saw/saw.hpp
        src/world/traps/saw/chain_saw.cpp
        src/world/traps/saw/chain_saw.hpp
        src/world/traps/saw/floor_saw.cpp
        src/world/traps/saw/floor_saw.hpp
        src/structs/line_path.hpp
        src/world/traps/spike_head/spike_head.cpp
        src/world/traps/spike_head/spike_head.hpp
        src/world/traps/trap.hpp
        src/world/traps/trap_manager.cpp
        src/world/traps/trap_manager.hpp
        src/world/traps/spiked_ball/spiked_ball.cpp
        src/world/traps/spiked_ball/spiked_ball.hpp
        src/world/traps/spiked_ball/pendulum_spiked_ball.cpp
        src/world/traps/spiked_ball/pendulum_spiked_ball.hpp
        src/world/traps/spiked_ball/circular_spiked_ball.cpp
        src/world/traps/spiked_ball/circular_spiked_ball.hpp
        src/world/fruits/fruit.cpp
        src/world/fruits/fruit.hpp
        src/world/fruits/fruit_manager.cpp
        src/world/fruits/fruit_manager.hpp
        src/structs/level_details.hpp
        src/enums/origin.hpp
        src/enums/orientation.hpp
        src/enums/particle_type.hpp
        src/gui/gui_element.cpp
        src/gui/gui_element.hpp
        src/gui/button.cpp
        src/gui/button.hpp
        src/gui/gui_container.cpp
        src/gui/gui_container.hpp
        src/gui/text_button.cpp
        src/gui/text_button.hpp
        src/gui/sprite_element.cpp
        src/gui/sprite_element.hpp
        src/gui/text_element.cpp
        src/gui/text_element.hpp
        src/gui/slider.cpp
        src/gui/slider.hpp
        src/gui/gui_builder.cpp
        src/gui/gui_builder.hpp
        src/states/settings_state.cpp
        src/states/settings_state.hpp
        src/states/pause_state.cpp
        src/states/pause_state.hpp
        src/states/game_over_state.cpp
        src/states/game_over_state.hpp
        src/states/key_binding_state.cpp
        src/states/key_binding_state.hpp
        src/gui/gui_includes.hpp
        src/structs/colors.hpp
        src/structs/settings.hpp
        src/states/pre_game_loading_state.cpp
        src/states/pre_game_loading_state.hpp
        src/audio/music_player.cpp
        src/audio/music_player.hpp
        src/audio/sound_player.cpp
        src/audio/sound_player.hpp
        src/world/cursor.cpp
        src/world/cursor.hpp
        src/world/finish_cup.cpp
        src/world/finish_cup.hpp
        src/utilities/easing_functions.cpp
        src/utilities/easing_functions.hpp)

set(SFML_STATIC_LIBRARIES true)

target_compile_definitions(Pixel_Adventure PRIVATE SFML_STATIC)

find_package(SFML COMPONENTS audio window graphics system REQUIRED)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML libraries not found")
endif ()

target_include_directories(Pixel_Adventure PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(Pixel_Adventure PRIVATE sfml-audio sfml-window sfml-graphics sfml-system)
target_link_options(Pixel_Adventure PRIVATE -static "-Wl,--allow-multiple-definition")
