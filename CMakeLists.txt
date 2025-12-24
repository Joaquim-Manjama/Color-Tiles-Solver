cmake_minimum_required(VERSION 3.16)
project(Color-Tiles-Solver)

add_executable(main
    main.cpp
    src/board.cpp
    src/position.cpp
    src/game.cpp
)

target_include_directories(main PRIVATE include)
