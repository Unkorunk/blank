cmake_minimum_required(VERSION 3.2)
project(blank_engine)
project(blank_game)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(submodules/json)
add_subdirectory(submodules/glm)
add_subdirectory(submodules/glfw)
add_subdirectory(submodules/glew/build/cmake)
add_subdirectory(submodules/freetype2)

add_library(blank_core
        src/Entry.cpp src/Entry.h
        src/Shader.cpp src/Shader.h
        src/Settings.cpp src/Settings.h
        src/GUI/Component.cpp src/GUI/Component.h
        src/GUI/Button.cpp src/GUI/Button.h
        src/GUI/Label.cpp src/GUI/Label.h
        src/GUI/Font.cpp src/GUI/Font.h
        src/GUI/Texture.cpp src/GUI/Texture.h
        src/GUI/Color.cpp src/GUI/Color.h src/GUI/ITreeStructure.cpp src/GUI/ITreeStructure.h src/MouseEvent.h)

add_executable(blank_game src/Game/Game.cpp)
add_executable(blank_engine src/Engine/Engine.cpp)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

find_package(OpenGL REQUIRED)

target_include_directories(blank_core PUBLIC ${PROJECT_SOURCE_DIR}/submodules/glew/include)
target_link_libraries(blank_core freetype glew_s glfw OpenGL::GL nlohmann_json::nlohmann_json glm::glm)

target_link_libraries(blank_engine blank_core)
target_link_libraries(blank_game blank_core)

configure_file(settings.json settings.json COPYONLY)
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
