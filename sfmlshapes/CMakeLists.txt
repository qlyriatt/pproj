cmake_minimum_required(VERSION 3.0.0)
project(sfmlshapes VERSION 0.1.0)


find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
if(!${SMFL_FOUND})
    message(FATAL_ERROR "SFML not found")
endif()

add_executable(sfmlshapes sfmlshapes.cpp)

target_include_directories(sfmlshapes PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(sfmlshapes sfml-graphics sfml-system sfml-window)