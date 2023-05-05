cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(mario)

find_package(SFML COMPONENTS graphics window system network audio REQUIRED) 
find_package(spdlog REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(include)

set(MARIO_SRC src/Mario)
set(SOURCES ${MARIO_SRC}/Game.cpp ${MARIO_SRC}/Mario.cpp ${MARIO_SRC}/Object.cpp ${MARIO_SRC}/ScoreBoard.cpp ${MARIO_SRC}/Turtle.cpp ${MARIO_SRC}/Background.cpp)
add_library(MARIO_LIB ${SOURCES})
target_link_libraries(MARIO_LIB sfml-graphics sfml-window spdlog::spdlog)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}")
target_link_libraries(${PROJECT_NAME} MARIO_LIB)
