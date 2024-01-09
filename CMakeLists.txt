cmake_minimum_required(VERSION 3.27)
project(Platformer)

set(CMAKE_CXX_STANDARD 23)

add_executable(Platformer
        src/main.cpp
        src/game.cpp
        src/game.hpp
        src/utils.hpp
        src/utils.cpp
        src/asset_managers/asset_manager.hpp
        src/asset_managers/asset_manager.inl
        src/asset_managers/texture_manager.hpp
        src/asset_managers/font_manager.hpp
        src/asset_managers/sound_buffer_manager.hpp
        src/asset_managers/music_manager.hpp)

set(SFML_STATIC_LIBRARIES true)

target_compile_definitions(Platformer PRIVATE SFML_STATIC)

find_package(SFML COMPONENTS audio window graphics system REQUIRED)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML libraries not found")
endif ()

target_include_directories(Platformer PRIVATE ${CMAKE_CURRENT_LIST_DIR}SFML_INCLUDES/include/)

target_link_libraries(Platformer PRIVATE sfml-audio sfml-window sfml-graphics sfml-system)