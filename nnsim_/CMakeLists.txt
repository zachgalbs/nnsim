cmake_minimum_required(VERSION 3.20)
project(nnsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(RAYLIB_USE_STATIC_LIBS "Link against the static raylib library" ON)
set(raylib_USE_STATIC_LIBS "${RAYLIB_USE_STATIC_LIBS}")

find_package(raylib REQUIRED)

add_executable(nnsim
    main.cpp
        main.cpp
        constants.h
)

target_link_libraries(nnsim PRIVATE raylib::raylib)
