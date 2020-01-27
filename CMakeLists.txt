cmake_minimum_required(VERSION 3.15)
project(blank)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${nlohmann_json_source} ${CMAKE_CURRENT_BINARY_DIR}/json-3.7.3)

add_executable(blank main.cpp Entry.cpp Entry.h Shader.cpp Shader.h)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3.2 REQUIRED)

target_link_libraries(blank glfw GLEW::GLEW OpenGL::GL nlohmann_json::nlohmann_json)

configure_file(settings.json settings.json COPYONLY)
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})