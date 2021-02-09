//
// Created by unkorunk on 03.03.2020.
//

#include "Blank.h"

Blank::Blank() {
    if (!glfwInit()) {
        throw std::runtime_error("[GLFW] failed init");
    }

    try {
        this->awake();
    } catch (std::exception &ex) {
        glfwTerminate();
        throw ex;
    }

    window = glfwCreateWindow(Settings::getInstance().get<int>("width"),
                              Settings::getInstance().get<int>("height"),
                              Settings::getInstance().get<std::string>("title").c_str(),
                              Settings::getInstance().get<bool>("fullscreen") ? glfwGetPrimaryMonitor() : nullptr,
                              nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("[GLFW] failed create window");
    }

    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("[GLEW] failed init");
    }

    try {
        this->start();
    } catch (std::exception &ex) {
        glfwTerminate();
        throw ex;
    }

}

Blank::~Blank()
{
    for (IManager* manager : this->managers.getChildren()) {
        delete manager;
    }
}

int Blank::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        try {
            this->update();
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;

            glfwTerminate();
            return 1;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        const char *description;
        if (glfwGetError(&description) != GLFW_NO_ERROR) {
            std::cerr << description << std::endl;

            glfwTerminate();
            return 1;
        }
    }

    glfwTerminate();

    return 0;
}

void Blank::awake() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Blank::start() {
    if (Settings::getInstance().get<bool>("vsync")) {
        glfwSwapInterval(1);
    }

    glClearColor(0.0f, 0.3f, 0.65f, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(this->getWindow(), [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    this->managers.addChild(new SceneManager(this));
    this->managers.addChild(new MouseManager(this));
    this->managers.addChild(new ResourceManager(this));
    this->managers.addChild(new PhysicsManager(this));
    this->managers.addChild(new KeyboardManager(this));

    for (IManager* manager : this->managers.getChildren()) {
        manager->start();
    }

    time_prev_frame = std::chrono::system_clock::now();
}

void Blank::update() {
    std::chrono::system_clock::time_point time_now_frame = std::chrono::system_clock::now();
    auto delta_time_ms = std::chrono::duration_cast<std::chrono::microseconds>(
            time_now_frame - time_prev_frame).count();
    time_prev_frame = time_now_frame;
    float delta_time = delta_time_ms / 1000000.0f;

    this->updateProj();

    IScene* scene = this->getManager<SceneManager>()->getScene();
    if (scene != nullptr) {
        scene->update(delta_time);

        scene->getShader()->activate();
        for (GameObject* game_object : scene->getChildren()) {
            game_object->update();
        }
        scene->getShader()->deactivate();
    }

    for (IManager* manager : this->managers.getChildren()) {
        manager->update(delta_time);
    }
}

GLFWwindow *Blank::getWindow() const {
    return this->window;
}

void Blank::updateProj() {
    glfwGetFramebufferSize(this->getWindow(), &window_width, &window_height);
    float ratio = static_cast<float>(window_width) / window_height;
    projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
}

glm::mat4 Blank::getProjection() const {
    return this->projection;
}

Vector2f Blank::unProj(const Vector2f& mouse_position) const {
    float ratio = static_cast<float>(window_width) / window_height;
    glm::vec4 un_proj = glm::inverse(projection) * glm::vec4(mouse_position.getX(), mouse_position.getY(), 1.0f, 1.0f);
    return Vector2f(2.0f * un_proj.x / window_width - ratio, -2.0f * un_proj.y / window_height + 1.0f);
}
