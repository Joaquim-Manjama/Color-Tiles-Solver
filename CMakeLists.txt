cmake_minimum_required(VERSION 3.16)
project(Color-Tiles-Solver)

# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

add_executable(main
    main.cpp
    src/board.cpp
    src/position.cpp
    src/game.cpp
    src/solver.cpp
)

target_link_libraries(main raylib)

target_include_directories(main PRIVATE include)
