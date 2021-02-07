//
// Created by unkorunk on 03.03.2020.
//

#include <memory>
#include <string>

#include <Blank.h>
#include <ResourceManager.h>
#include <Scene/SceneManager.h>
#include <Scene/IScene.h>
#include <GameObject/GameObject.h>
#include <GUI/Button.h>
#include <GUI/Font.h>
#include <GUI/Label.h>

class FPSScene : public IScene {
public:
    void start() override {
        this->roboto_font = std::unique_ptr<GUI::Font>(GUI::Font::loadFont("./assets/fonts/some_font.ttf"));
        this->roboto_font->setPixelSizes(0, 64);

        this->fps_label = std::make_unique<GUI::Label>();

        Component::Transform* fps_label_transform = fps_label->getComponent<Component::Transform>();
        fps_label_transform->setPosition(Vector3f(-4.0f / 3.0f, 1.0f, 0.0f));
        this->fps_label->setHeight(0.08f);
        this->fps_label->setFont(roboto_font.get());

        this->addChild(this->fps_label.get());
    }

    void update(float delta_time) override {
        this->mytime_fps += delta_time;
        if (this->mytime_fps > 1.0f) {
            this->fps_label->setText(std::to_string(static_cast<size_t>(this->frames / this->mytime_fps)));

            this->mytime_fps = 0.0f;
            this->frames = 0;
        }

        this->frames++;
    }

protected:
    std::unique_ptr<GUI::Font> roboto_font;

private:
    std::unique_ptr<GUI::Label> fps_label;
    float mytime_fps = 0.0f;
    size_t frames = 0;

};

class GameScene : public FPSScene {
public:
    void start() override {
        FPSScene::start();

        const GLsizei texture_width = 33;
        const GLsizei texture_height = 33;

        std::unique_ptr<uint8_t[]> pixels(new uint8_t[texture_width * texture_height * 4]());

        for (GLsizei i = 0; i < texture_height; i++) {
            for (GLsizei j = 0; j < texture_width; j++) {
                if ((i - 16) * (i - 16) + (j - 16) * (j - 16) <= 16 * 16) {
                    pixels[4 * (i * texture_width + j) + 3] = 255;
                }
            }
        }

        texture_player.setData(texture_width, texture_height, pixels.get());

        transform_player = texture_player.getComponent<Component::Transform>();
        transform_player->setSize(0.1f, 0.1f, 1.0f);

        this->addChild(&texture_player);

        this->mouse = this->getBlank()->getManager<MouseManager>();
    }

    void update(float delta_time) override {
        FPSScene::update(delta_time);

        transform_player->setPosition(Vector3f(position_player - Vector2f(transform_player->getWidth() / 2.0f, -transform_player->getHeight() / 2.0f)));

        // TODO: FIX: sometimes no MOUSE_DOWN event
        if (this->mouse->getMouseEvent() == MouseEvent::MOUSE_DOWN || this->mouse->getMouseEvent() == MouseEvent::MOUSE_PRESS) {
            target_position = this->getBlank()->unProj(
                this->mouse->getMousePosition()
            );
        }

        if (Vector2f::distanceSqr(target_position, position_player) > 1e-4) {
            Vector2f dir = (target_position - position_player).normalized();
            
            position_player = position_player + speed_player * dir * delta_time;
        }
    }
    
private:
    GUI::Texture texture_player;
    Component::Transform* transform_player;
    Vector2f position_player;
    const float speed_player = 2.0f;

    Vector2f target_position;

    MouseManager* mouse;

};

class TestScene : public FPSScene {
public:
    void start() override {
        FPSScene::start();

        this->button_start = std::make_unique<GUI::Button>();

        this->button_start->setX(-0.5f / 2.0f);
        this->button_start->setY(0.15f / 2.0f);
        this->button_start->setWidth(1.0f / 2.0f);
        this->button_start->setHeight(0.3f / 2.0f);
        this->button_start->setMouseCallback(MouseEvent::MOUSE_UP, [this](const Vector2f& position) {
            this->getBlank()->getManager<SceneManager>()->create<GameScene>();
        });

        this->button_start->setFont(roboto_font.get());
        this->button_start->setText("Start");

        this->button_press_me = std::make_unique<GUI::Button>();
        this->button_press_me->setX(-0.5f / 2.0f);
        this->button_press_me->setY(1.0f / 2.0f);
        this->button_press_me->setWidth(1.0f / 2.0f);
        this->button_press_me->setHeight(0.3f / 2.0f);

        this->button_press_me->setFont(roboto_font.get());
        this->button_press_me->setText("Press Me");

        this->game_object_ui.addChild(button_start.get());
        this->game_object_ui.addChild(button_press_me.get());

        this->addChild(&game_object_ui);

        this->mouse = this->getBlank()->getManager<MouseManager>();
    }

    void update(float delta_time) override {
        FPSScene::update(delta_time);

        if (this->button_press_me->getMouseEvent() == MouseEvent::MOUSE_DOWN || this->button_press_me->getMouseEvent() == MouseEvent::MOUSE_PRESS) {
            Component::Transform* button_rotate_tranform = this->button_press_me->getComponent<Component::Transform>();
            button_rotate_tranform->setRotation(
                button_rotate_tranform->getRotation() + Vector3f(0.0f, 0.0f, 3.0f) * delta_time
            );
        }
    }

private:
    std::unique_ptr<GUI::Button> button_start;
    std::unique_ptr<GUI::Button> button_press_me;

    GameObject game_object_ui;

    MouseManager* mouse;

};

int main() {
    std::unique_ptr<Blank> blank(new Blank());

    blank->getManager<SceneManager>()->create<TestScene>();

    return blank->run();
}
