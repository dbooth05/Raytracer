cmake_minimum_required(VERSION 3.10)
project(Raytracer)

file(GLOB SOURCES src/*.cpp)

add_executable(Raytracer
    ${SOURCES}
    src/main.cpp
)

target_include_directories(Raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}/BaseEngine/include
)

target_link_libraries(Raytracer PRIVATE
    BaseEngine
)

set_target_properties(Raytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)
