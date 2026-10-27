cmake_minimum_required(VERSION 3.23)

project(LED_Matrix CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

add_definitions(-DLOG_LEVEL=1)

add_executable( LED_Matrix )

target_sources( LED_Matrix
    PRIVATE
        src/main.cpp
        src/games/Player.cpp
        src/games/MainMenu.cpp
        src/display/Image.cpp
        src/display/drivers/Stdout.cpp
        src/display/drivers/Sdl.cpp
        include/logger/logger.cpp
)

target_include_directories( LED_Matrix
    PRIVATE
        include/schrift
        include/logger
)

target_link_libraries( LED_Matrix ${SDL2_LIBRARIES} )
