cmake_minimum_required(VERSION 3.2)
project(blank)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(submodules/json)
add_subdirectory(submodules/glm)
add_subdirectory(submodules/glfw)

# https://github.com/nigels-com/glew
# TODO: Setting add_subdirectory
add_library(glew INTERFACE)
target_include_directories(glew INTERFACE ${CMAKE_SOURCE_DIR}/submodules/glew/include)
target_link_libraries(glew INTERFACE ${CMAKE_SOURCE_DIR}/submodules/glew/lib/Debug/x64/glew32sd.lib)
add_definitions(-DGLEW_STATIC)

add_executable(blank main.cpp Entry.cpp Entry.h Shader.cpp Shader.h)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(blank glew glfw OpenGL::GL nlohmann_json::nlohmann_json glm::glm)

configure_file(settings.json settings.json COPYONLY)
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
