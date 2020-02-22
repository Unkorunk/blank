//
// Created by unkorunk on 26.01.2020.
//

#include "Entry.h"

Entry::Entry() : window() {}

Entry::~Entry() = default;

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
        Mouse::getInstance().mouseButtonCallback(window, button, action, mods);
    });
    glfwSetCursorEnterCallback(this->window, [](GLFWwindow *window, int entered) {
        Mouse::getInstance().mouseEnterCallback(window, entered);
    });
    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos) {
        Mouse::getInstance().mouseMoveCallback(window, xpos, ypos);
    });

    // example
    roboto_font = std::unique_ptr<GUI::Font>(GUI::Font::loadFont("./assets/fonts/some_font.ttf"));
    roboto_font->setPixelSizes(0, 32);

    test_button.setX(-0.2f);
    test_button.setY(0.5f);
    test_button.setWidth(1.0f);
    test_button.setHeight(0.3f);
    test_button.setMouseCallback(MouseEvent::MOUSE_DOWN, [](float x, float y) {
        std::cout << "Hello World" << std::endl;
    });

    test_label.setFont(roboto_font.get());
    test_label.setText("Test Button");

    test_button.addChild(&test_label);
    // ~example

    time_prev_frame = std::chrono::system_clock::now();
}

void Entry::update() {
    std::chrono::system_clock::time_point time_now_frame = std::chrono::system_clock::now();
    auto delta_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            time_now_frame - time_prev_frame).count();
    time_prev_frame = time_now_frame;
    float delta_time = delta_time_ms / 1000.0f;

    // example
    Shader &shader = shaders.at("default");
    shader.activate();

    test_button.draw(&shader);

    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);
    std::pair<float, float> mouse_position = Mouse::getInstance().getMousePosition();
    float mouse_x = 2.0f * mouse_position.first / window_width - 1.0f,
            mouse_y = -2.0f * mouse_position.second / window_height + 1.0f;

    bool mouse_on_button = (mouse_x > test_button.getX() ||
                            abs(mouse_x - test_button.getX()) < std::numeric_limits<float>::epsilon()) &&
                           (mouse_y < test_button.getY() ||
                            abs(mouse_y - test_button.getY()) < std::numeric_limits<float>::epsilon()) &&
                           mouse_x < test_button.getX() + test_button.getWidth() &&
                           mouse_y > test_button.getY() - test_button.getHeight();

    if (mouse_on_button) {
        test_button.mouseEvent(Mouse::getInstance().getMouseEvent(), mouse_x, mouse_y);
    }

    shader.deactivate();
    // ~example

    Mouse::getInstance().update();
}

void Entry::setWindow(GLFWwindow* window) {
    this->window = window;
}
