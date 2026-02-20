cmake_minimum_required(VERSION 3.28)
project(GettingModuleToWork LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(math_module REQUIRED)

add_executable(app)

target_sources(app
    PRIVATE
        main.cpp
)

target_link_libraries(app PRIVATE math_module::math_module)
