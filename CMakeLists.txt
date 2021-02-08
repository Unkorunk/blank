cmake_minimum_required(VERSION 3.2)

project(blank)

set(CMAKE_CXX_STANDARD 17)

set(BOX2D_BUILD_TESTBED OFF)

add_subdirectory(submodules/json)
add_subdirectory(submodules/glm)
add_subdirectory(submodules/glfw)
add_subdirectory(submodules/glew/build/cmake)
add_subdirectory(submodules/freetype2)
add_subdirectory(submodules/box2d)

add_library(blank
        src/Blank.h src/Blank.cpp
        src/Shader.cpp src/Shader.h
        src/Settings.cpp src/Settings.h
        src/ITreeStructure.h
        src/ResourceManager.h
        src/GUI/UIComponent.cpp src/GUI/UIComponent.h
        src/GUI/Button.cpp src/GUI/Button.h
        src/GUI/Label.cpp src/GUI/Label.h
        src/GUI/Font.cpp src/GUI/Font.h
        src/GUI/Texture.cpp src/GUI/Texture.h
        src/GUI/Color.cpp src/GUI/Color.h
        src/Mouse/MouseEvent.h
        src/Mouse/MouseManager.cpp src/Mouse/MouseManager.h
        src/Utility/Vector2f.cpp src/Utility/Vector2f.h
        src/Utility/Vector3f.cpp src/Utility/Vector3f.h
        src/Scene/SceneManager.cpp src/Scene/SceneManager.h
        src/Scene/IScene.h
        src/GameObject/GameObject.cpp src/GameObject/GameObject.h
        src/Component/IComponent.h
        src/Component/Transform.cpp src/Component/Transform.h
        src/Component/InputMouse.cpp src/Component/InputMouse.h
        src/IManager.h
        src/Physics/PhysicsManager.cpp src/Physics/PhysicsManager.h
        src/Component/Physics.cpp src/Component/Physics.h)
target_include_directories(blank PUBLIC src)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -Wextra -pedantic -Werror")
endif()

find_package(OpenGL REQUIRED)

target_include_directories(blank PUBLIC ${PROJECT_SOURCE_DIR}/submodules/glew/include)
target_link_libraries(blank box2d freetype glew_s glfw OpenGL::GL nlohmann_json::nlohmann_json glm::glm)

add_executable(example example/main.cpp)
target_link_libraries(example PUBLIC blank)

add_custom_command(TARGET example PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:example>/assets)
