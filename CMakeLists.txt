cmake_minimum_required(VERSION 3.29)
project(tower_c C)

set(CMAKE_C_STANDARD 23)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} REQUIRED)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} raylib)
