cmake_minimum_required(VERSION 3.10)
project(game)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(game
  src/main.cpp
  )
target_link_libraries(game PRIVATE SDL2::Main SDL2::TTF )
target_include_directories(game PRIVATE include )