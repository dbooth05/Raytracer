cmake_minimum_required(VERSION 3.10)
project(BaseEngineApp)

file(GLOB APP_SOURCES src/*.cpp)

add_executable(BaseEngineApp ${APP_SOURCES} src/BaseEngineApp.cpp)

target_include_directories(BaseEngineApp PRIVATE ${CMAKE_SOURCE_DIR}/BaseEngine/include)

target_link_libraries(BaseEngineApp PRIVATE BaseEngine)
