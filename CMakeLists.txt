cmake_minimum_required(VERSION 3.20)
project(nnsim CXX)
set(CMAKE_CXX_STANDARD 20)

# create the executable from main.cpp
add_executable(nnsim main.cpp
        main.cpp)

# expose local cmake modules and link raylib for rendering
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(raylib REQUIRED MODULE)
target_link_libraries(nnsim PRIVATE raylib::raylib)

