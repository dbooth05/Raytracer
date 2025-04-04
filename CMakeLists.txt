cmake_minimum_required(VERSION 3.10)
project(Raytracer)

add_subdirectory(libs/BaseEngine)

file(GLOB SOURCES src/*.cpp)

add_executable(Raytracer
    ${SOURCES}
)

target_include_directories(Raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/BaseEngine/include
)

target_link_libraries(Raytracer PRIVATE
    BaseEngine
)
