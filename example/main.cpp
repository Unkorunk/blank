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
#include <Component/Physics.h>

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

        this->keyboard = this->getBlank()->getManager<KeyboardManager>();
    }

    void update(float delta_time) override {
        if (keyboard->getKeyboardEvent(KeyboardKey::KEY_F) == KeyboardEvent::UP) {
            this->fps_label_enabled = !this->fps_label_enabled;
        }

        if (!this->fps_label_enabled) {
            this->fps_label->setText("");
            return;
        }

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
    bool fps_label_enabled = true;

    KeyboardManager* keyboard;

};

class GameScene : public FPSScene {
public:
    void start() override {
        FPSScene::start();

        createCursor();
        createPlayer();
        createGround();

        this->mouse = this->getBlank()->getManager<MouseManager>();
        this->mouse->hideCursor();
    }

    void update(float delta_time) override {
        FPSScene::update(delta_time);

        Vector2f mouse_position = this->getBlank()->unProj(
            this->mouse->getMousePosition()
        );

        // TODO: FIX: sometimes no MOUSE_DOWN event
        if (this->mouse->getMouseEvent() == MouseEvent::DOWN ||
            this->mouse->getMouseEvent() == MouseEvent::PRESS) {
            physics_player->addForce(
                (mouse_position - transform_player->getPosition2D()).normalized() * 150.0f
            );
        }

        transform_cursor->setPosition2D(
            mouse_position + Vector2f(
                -transform_cursor->getWidth() / 2.0f,
                transform_cursor->getHeight() / 2.0f
            )
        );
    }

private:
    GUI::Texture cursor{32, 32}, player{32, 32}, ground{32, 32};
    Component::Transform *transform_cursor, *transform_player;
    std::unique_ptr<Component::Physics> physics_player, physics_ground;

    MouseManager* mouse;

    void createCursor() {
        for (GLsizei i = 0; i < 32; i++) {
            for (GLsizei j = 0; j < 32; j++) {
                if ((i - 16) * (i - 16) + (j - 16) * (j - 16) <= 16 * 16) {
                    cursor.setPixel(i, j, GUI::Color(255, 0, 0));
                }
            }
        }

        transform_cursor = cursor.getComponent<Component::Transform>();
        transform_cursor->setZ(1.0f);
        transform_cursor->setSize2D(0.025f, 0.025f);

        this->addChild(&cursor);
    }

    void createPlayer() {
        for (GLsizei i = 0; i < 32; i++) {
            for (GLsizei j = 0; j < 32; j++) {
                if (i == 0 || i == 31 || j == 0 || j == 31) {
                    player.setPixel(i, j, GUI::Color(0, 0, 0));
                } else {
                    player.setPixel(i, j, GUI::Color(180, 67, 134));
                }
            }
        }

        transform_player = player.getComponent<Component::Transform>();
        transform_player->setZ(0.0f);
        transform_player->setSize2D(0.1f, 0.1f);

        physics_player = std::make_unique<Component::Physics>();
        player.addComponent(physics_player.get());

        this->addChild(&player);
    }

    void createGround() {
        for (GLsizei i = 0; i < 32; i++) {
            for (GLsizei j = 0; j < 32; j++) {
                GUI::Color color;
                if (j > 22) {
                    color = GUI::Color(0, 69, 0);
                } else if (j > 18) {
                    color = (rand() % 2 == 0 ? GUI::Color(139, 69, 19) : GUI::Color(0, 69, 0));
                } else {
                    color = GUI::Color(139, 69, 19);
                }

                ground.setPixel(i, j, color);
            }
        }

        physics_ground = std::make_unique<Component::Physics>();
        physics_ground->setIsStaticBody(true);
        ground.addComponent(physics_ground.get());

        Component::Transform* ground_transform = ground.getComponent<Component::Transform>();
        ground_transform->setSize2D(2.0f * 4.0f / 3.0f, 0.1f);
        ground_transform->setPosition(-4.0f / 3.0f, -0.9f, 0.0f);
        ground_transform->setRotation(
            Vector3f(
                ground_transform->getRotation().getX(),
                ground_transform->getRotation().getY(),
                0.0f
            )
        );

        this->addChild(&ground);
    }

};

class TestScene : public FPSScene {
public:
    void start() override {
        FPSScene::start();

        this->button_click_me = std::make_unique<GUI::Button>();

        this->button_click_me->setX(-0.5f / 2.0f);
        this->button_click_me->setY(0.15f / 2.0f);
        this->button_click_me->setWidth(1.0f / 2.0f);
        this->button_click_me->setHeight(0.3f / 2.0f);
        this->button_click_me->setMouseCallback(MouseEvent::UP, [this](const Vector2f& position) {
            this->getBlank()->getManager<SceneManager>()->create<GameScene>();
        });

        this->button_click_me->setFont(roboto_font.get());
        this->button_click_me->setText("Click Me");

        this->button_hover_me = std::make_unique<GUI::Button>();
        this->button_hover_me->setX(-0.5f / 2.0f);
        this->button_hover_me->setY(1.0f / 2.0f);
        this->button_hover_me->setWidth(1.0f / 2.0f);
        this->button_hover_me->setHeight(0.3f / 2.0f);

        this->button_hover_me->setFont(roboto_font.get());
        this->button_hover_me->setText("Hover Me");

        this->game_object_ui.addChild(button_click_me.get());
        this->game_object_ui.addChild(button_hover_me.get());

        this->addChild(&game_object_ui);

        this->mouse = this->getBlank()->getManager<MouseManager>();
    }

    void update(float delta_time) override {
        FPSScene::update(delta_time);

        if (this->button_hover_me->getMouseEvent() == MouseEvent::MOVE ||
            this->button_hover_me->getMouseEvent() == MouseEvent::CONTAINS) {
            Component::Transform* button_rotate_tranform = this->button_hover_me->getComponent<Component::Transform>();
            button_rotate_tranform->setRotation(
                button_rotate_tranform->getRotation() + Vector3f(0.0f, 0.0f, 3.0f) * delta_time
            );
        }
    }

private:
    std::unique_ptr<GUI::Button> button_click_me;
    std::unique_ptr<GUI::Button> button_hover_me;

    GameObject game_object_ui;

    MouseManager* mouse;

};

int main() {
    std::unique_ptr<Blank> blank(new Blank());

    blank->getManager<SceneManager>()->create<TestScene>();

    return blank->run();
}
