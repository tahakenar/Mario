cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(mario)
 
# find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED) 
include_directories(include)
include_directories(include/Mario)
# include_directories(${SFML_INCLUDE_DIR})

set(MARIO_SRC src/Mario)
set(SOURCES ${MARIO_SRC}/Game.cpp ${MARIO_SRC}/Mario.cpp ${MARIO_SRC}/Object.cpp ${MARIO_SRC}/ScoreBoard.cpp ${MARIO_SRC}/Turtle.cpp)
add_library(MARIO_LIB ${SOURCES})
# target_link_libraries(MARIO_LIB sfml-graphics sfml-window)

add_executable(${PROJECT_NAME} src/main.cpp)
# target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}")
target_link_libraries(${PROJECT_NAME} MARIO_LIB)
