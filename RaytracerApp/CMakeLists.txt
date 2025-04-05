cmake_minimum_required(VERSION 3.10)
project(Raytracer)

# set default build type to release unless debug specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# conditional compilation definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
endif()

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
