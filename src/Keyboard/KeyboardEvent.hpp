#pragma once

#include <limits>

enum class KeyboardEvent {
    UP = GLFW_RELEASE,
    DOWN = GLFW_PRESS,
    PRESS = GLFW_REPEAT,
    NONE
};
