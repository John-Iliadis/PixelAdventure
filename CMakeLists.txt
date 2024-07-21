cmake_minimum_required(VERSION 3.27)
project(PixelAdventure)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(FATAL_ERROR "This project requires a mingw compiler, since SFML is not found when using msvc. I can't be bothered fixing it.")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME_DEBUG ${PROJECT_NAME}-d
    OUTPUT_NAME_RELEASE ${PROJECT_NAME})

set(SFML_STATIC_LIBRARIES true)

target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

find_package(SFML COMPONENTS audio window graphics system REQUIRED)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML libraries not found")
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio sfml-window sfml-graphics sfml-system)

target_link_options(${PROJECT_NAME} PRIVATE -static "-Wl,--allow-multiple-definition")
