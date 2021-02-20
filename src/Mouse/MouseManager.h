#pragma once

#include <utility>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IManager.h"
#include "MouseEvent.h"
#include "MouseKey.hpp"
#include "Utility/Vector2f.h"

class MouseManager : public IManager {
public:
    explicit MouseManager(Blank *blank);
    virtual ~MouseManager() = default;

    void start() override;
    void update(float delta_time) override;
    void lateUpdate() override;

    Vector2f getMousePosition() const;

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void mouseEnterCallback(GLFWwindow* window, int entered);
    void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

    void hideCursor();
    void disableCursor();
    void enableCursor();

    bool check(const MouseKey& mouse_key, const MouseEvent& mouse_event) {
        return check(this->getMouseEvent(mouse_key), mouse_event);
    }

    bool isMove() const {
        return is_move;
    }

    bool isContains() const {
        return is_contains;
    }

    bool isEnter() const {
        return is_enter;
    }

    bool isLeave() const {
        return is_leave;
    }

private:
    std::unordered_map<MouseKey, MouseEvent> events;
    std::unordered_map<MouseKey, MouseEvent> old_events;

    Vector2f mouse_position;
    bool is_move = false, is_contains = false, is_enter = false, is_leave = false;

    void setMouseEvent(const MouseKey& mouse_key, const MouseEvent& mouse_event);
    void unsetMouseEvent(const MouseKey& mouse_key, const MouseEvent& mouse_event);

    static bool check(const MouseEvent& lhs, const MouseEvent& rhs) {
        using T = std::underlying_type_t<MouseEvent>;
        return (static_cast<T>(lhs) & static_cast<T>(rhs)) == static_cast<T>(rhs);
    }

    MouseEvent getMouseEvent(const MouseKey& mouse_key) {
        if (events.count(mouse_key)) {
            return events.at(mouse_key);
        }

        return MouseEvent::NONE;
    }

    MouseEvent getOldMouseEvent(const MouseKey& mouse_key) {
        if (old_events.count(mouse_key)) {
            return old_events.at(mouse_key);
        }

        return MouseEvent::NONE;
    }

};
