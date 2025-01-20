cmake_minimum_required(VERSION 3.10)
project(Raytracer LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set OpenGL preference
cmake_policy(SET CMP0072 NEW)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add GLEW manually
find_library(GLEW_LIBRARY GLEW)
include_directories(/usr/include/GL)

# Find GLM
find_package(glm REQUIRED)

# imgui
set(IMGUI_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_sdl2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp
)

# Source files
set(SOURCES
  src/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/application)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/raytracer)

# Link libs
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} glm::glm)