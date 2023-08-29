cmake_minimum_required(VERSION 3.16)
project(snake C)

set(CMAKE_C_STANDARD 99)

add_executable(snake main.c)

target_link_libraries(snake pthread)
# 在msys2下，使用pacman -S mingw-w64-x86_64-ncurses安装
# 得到的库名为ncursesw，而不是ncurses! 这点非常奇怪
target_link_libraries(snake ncursesw)