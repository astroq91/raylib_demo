cmake_minimum_required(VERSION 3.3)
project(RaylibDemo)

find_package(raylib REQUIRED)
add_subdirectory(external/box2d)

add_executable(RaylibDemo)

target_sources(RaylibDemo
  PRIVATE
    src/main.c
)

target_link_libraries(RaylibDemo
  PRIVATE
    raylib
    box2d
)
