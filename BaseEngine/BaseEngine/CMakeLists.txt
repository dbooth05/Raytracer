cmake_minimum_required(VERSION 3.10)
project(BaseEngine)

# Find Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

# Gather engine sources
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)
file(GLOB_RECURSE ENGINE_HEADERS include/*.h libs/stb/*.h)
# set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR/src/application.cpp})

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)

# create static lib
add_library(BaseEngine STATIC
    src/application.cpp
    src/image.cpp
    src/random.cpp
    src/input.cpp
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
    ${IMGUI_SOURCES}
)

# include dirs
target_include_directories(BaseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/input
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb
)

# link libs
target_link_libraries(BaseEngine PUBLIC Vulkan::Vulkan glfw)
