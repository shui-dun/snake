cmake_minimum_required(VERSION 3.16)
project(snake C)

set(CMAKE_C_STANDARD 99)

add_executable(snake main.c)

target_link_libraries(snake pthread)
target_link_libraries(snake ncurses)