#include "KeyboardManager.hpp"
#include "Blank.h"

KeyboardManager::KeyboardManager(Blank* blank) : IManager(blank) {}

void KeyboardManager::start() {
    glfwSetKeyCallback(this->getBlank()->getWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Blank* blank = static_cast<Blank*>(glfwGetWindowUserPointer(window));
        blank->getManager<KeyboardManager>()->keyboardKeyCallback(window, key, scancode, action, mods);
    });
}

void KeyboardManager::update(float delta_time) {
    for (auto& it : this->events) {
        if (it.second == KeyboardEvent::UP) {
            it.second = KeyboardEvent::NONE;
        }
    }
}

void KeyboardManager::keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    this->events[static_cast<KeyboardKey>(key)] = static_cast<KeyboardEvent>(action);
}

KeyboardEvent KeyboardManager::getKeyboardEvent(const KeyboardKey& key) const {
    if (this->events.count(key)) {
        return this->events.at(key);
    }

    return KeyboardEvent::NONE;
}
