//
// Created by unkorunk on 26.01.2020.
//

#include "Entry.h"

Entry::Entry() : window(), mouse_event(MouseEvent::MOUSE_NOT_CONTAINS) {}

Entry::~Entry() {

}

Entry &Entry::getInstance() {
    static Entry entry;
    return entry;
}

void Entry::awake() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Entry::start() {
    for (auto &shader_name : Settings::getInstance().getShaders()) {
        shaders.try_emplace(shader_name, shader_name);
    }

    glClearColor(0.0f, 0.4f, 0.75f, 0.0f);
    if (Settings::getInstance().get<std::string>("project_type") == "3d") {
        glEnable(GL_DEPTH_TEST);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {
        Entry::getInstance().mouseButtonCallback(window, button, action, mods);
    });
    glfwSetCursorEnterCallback(this->window, [](GLFWwindow *window, int entered) {
        Entry::getInstance().mouseEnterCallback(window, entered);
    });
    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos) {
        Entry::getInstance().mouseMoveCallback(window, xpos, ypos);
    });

    roboto_font = std::unique_ptr<GUI::Font>(GUI::Font::loadFont("./assets/fonts/Roboto-Light.ttf"));
    roboto_font->setPixelSizes(0, 32);

    test_button.setX(-0.2f);
    test_button.setY(0.5f);
    test_button.setWidth(1.0f);
    test_button.setHeight(1.0f);
    test_button.setMouseDownCallback([](GUI::Button *button, float x, float y) {
        button->setX(x - button->getWidth() / 2.0f);
        button->setY(y + button->getHeight() / 2.0f);
    });

    test_label.setFont(roboto_font.get());
    test_label.setText("Hello World");

    test_button.addChild(&test_label);

    time_prev_frame = std::chrono::system_clock::now();
}

void Entry::update() {
    std::chrono::system_clock::time_point time_now_frame = std::chrono::system_clock::now();
    auto delta_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            time_now_frame - time_prev_frame).count();
    time_prev_frame = time_now_frame;
    float delta_time = delta_time_ms / 1000.0f;

    Shader &shader = shaders.at("default");
    shader.activate();

    test_label.setText(std::to_string(rand()));

    test_button.draw(&shader);

    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);
    double mouse_x = 2.0 * mouse_position_x / window_width - 1.0,
            mouse_y = -2.0 * mouse_position_y / window_height + 1.0;
    if (mouse_event == MouseEvent::MOUSE_PRESS) {
        if ((mouse_x > test_button.getX() ||
             abs(mouse_x - test_button.getX()) < std::numeric_limits<float>::epsilon()) &&
            (mouse_y < test_button.getY() ||
             abs(mouse_y - test_button.getY()) < std::numeric_limits<float>::epsilon()) &&
            mouse_x < test_button.getX() + test_button.getWidth() &&
            mouse_y > test_button.getY() - test_button.getHeight()) {
            test_button.mouseDown(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
        }
    }

    shader.deactivate();

    switch (mouse_event) {
        case MouseEvent::MOUSE_DOWN:
            mouse_event = MouseEvent::MOUSE_PRESS;
            break;
        case MouseEvent::MOUSE_UP:
        case MouseEvent::MOUSE_ENTER:
            mouse_event = MouseEvent::MOUSE_CONTAINS;
            break;
        case MouseEvent::MOUSE_LEAVE:
            mouse_event = MouseEvent::MOUSE_NOT_CONTAINS;
            break;
        default:
            break;
    }
}

void Entry::setWindow(GLFWwindow* window) {
    this->window = window;
}

void Entry::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            switch (mouse_event) {
                case MouseEvent::MOUSE_UP:
                case MouseEvent::MOUSE_ENTER:
                case MouseEvent::MOUSE_CONTAINS:
                case MouseEvent::MOUSE_MOVE:
                    mouse_event = MouseEvent::MOUSE_DOWN;
                    break;
                case MouseEvent::MOUSE_DOWN:
                case MouseEvent::MOUSE_PRESS:
                case MouseEvent::MOUSE_LEAVE:
                case MouseEvent::MOUSE_NOT_CONTAINS:
                    throw std::runtime_error("Undefined behavior");
            }
        } else if (action == GLFW_RELEASE) {
            mouse_event = MouseEvent::MOUSE_UP;
        } else {
            throw std::runtime_error("Undefined behavior");
        }
    }
}

void Entry::mouseEnterCallback(GLFWwindow *window, int entered) {
    if (entered == GLFW_TRUE) {
        this->mouse_event = MouseEvent::MOUSE_ENTER;
    } else if (entered == GLFW_FALSE) {
        this->mouse_event = MouseEvent::MOUSE_LEAVE;
    } else {
        throw std::runtime_error("Undefined behavior");
    }
}

void Entry::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    if (this->mouse_event != MouseEvent::MOUSE_PRESS) {
        this->mouse_event = MouseEvent::MOUSE_MOVE;
    }
    this->mouse_position_x = xpos;
    this->mouse_position_y = ypos;
}

