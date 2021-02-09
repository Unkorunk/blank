#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include "IManager.h"
#include "KeyboardEvent.hpp"
#include "KeyboardKey.hpp"

class KeyboardManager : public IManager {
public:
    explicit KeyboardManager(Blank* blank);
    virtual ~KeyboardManager() = default;

    void start() override;
    void update(float delta_time) override;
    void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    KeyboardEvent getKeyboardEvent(const KeyboardKey& key) const;

private:
    std::unordered_map<KeyboardKey, KeyboardEvent> events;

};
