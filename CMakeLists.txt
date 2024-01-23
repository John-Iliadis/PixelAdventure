cmake_minimum_required(VERSION 3.27)
project(Platformer)

set(CMAKE_CXX_STANDARD 23)

add_executable(Platformer
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
        src/states/state_identifiers.hpp
        src/states/state.cpp
        src/states/state.hpp
        src/states/game_context.hpp
        src/states/state_stack.cpp
        src/states/state_stack.hpp
        src/states/state_factory.cpp
        src/states/state_factory.hpp
        src/states/menu_state.cpp
        src/states/menu_state.hpp
        src/states/game_state.cpp
        src/states/game_state.hpp
        src/world/world.cpp
        src/world/world.hpp
        src/world/player/player.cpp
        src/world/player/player.hpp
        src/world/tile_map.cpp
        src/world/tile_map.hpp
        src/world/back_ground.cpp
        src/world/back_ground.hpp
        src/vendor/json.hpp
        src/world/collision.cpp
        src/world/collision.hpp
        src/animation/animation.cpp
        src/animation/animation.hpp
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
        src/world/player/death_state.cpp
        src/world/player/death_state.hpp
        src/world/player/player_platformer_data.hpp
        src/world/sprite_collider.cpp
        src/world/sprite_collider.hpp
        src/world/enums.hpp
        src/animation/animation_manager.cpp
        src/animation/animation_manager.hpp)

set(SFML_STATIC_LIBRARIES true)

target_compile_definitions(Platformer PRIVATE SFML_STATIC)

find_package(SFML COMPONENTS audio window graphics system REQUIRED)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML libraries not found")
endif ()

target_include_directories(Platformer PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(Platformer PRIVATE sfml-audio sfml-window sfml-graphics sfml-system)
