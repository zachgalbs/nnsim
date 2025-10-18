cmake_minimum_required(VERSION 3.20)
project(neurodrive CXX)
set(CMAKE_CXX_STANDARD 17)

# create the executable from main.cpp
add_executable(neurodrive src/main.cpp)

# link raylib for rendering
find_package(raylib REQUIRED)
target_link_libraries(neurodrive PRIVATE raylib)

