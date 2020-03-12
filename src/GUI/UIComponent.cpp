//
// Created by unkorunk on 13.02.2020.
//

#include "UIComponent.h"
#include "Blank.h"

namespace GUI {
    UIComponent::UIComponent() : transform(new Component::Transform()) {
        this->addComponent(this->transform.get());
    }

    void UIComponent::draw(Shader *shader) {
        if (Settings::getInstance().get<bool>("debug")) {
            shader->set("use_texture", 0);

            std::array<GLfloat, 8 * 3> vertices = {
                    transform->getX(), transform->getY(), 0.0f,
                    transform->getX() + transform->getWidth(), transform->getY(), 0.0f,
                    transform->getX() + transform->getWidth(), transform->getY(), 0.0f,
                    transform->getX() + transform->getWidth(), transform->getY() - transform->getHeight(), 0.0f,
                    transform->getX() + transform->getWidth(), transform->getY() - transform->getHeight(), 0.0f,
                    transform->getX(), transform->getY() - transform->getHeight(), 0.0f,
                    transform->getX(), transform->getY() - transform->getHeight(), 0.0f,
                    transform->getX(), transform->getY(), 0.0f
            };
            std::array<GLfloat, 8 * 4> colors = {};
            for (size_t i = 0; i < 8; i++) {
                colors[4 * i + 0] = 1.0f;
                colors[4 * i + 1] = 0.0f;
                colors[4 * i + 2] = 0.0f;
                colors[4 * i + 3] = 1.0f;
            }

            shader->set(2, colors.size() * sizeof(GLfloat), 4, colors.data());
            shader->set(0, vertices.size() * sizeof(GLfloat), 3, vertices.data());

            glDrawArrays(GL_LINES, 0, 2 * 4);
        }
    }

	void UIComponent::update()
	{
        GameObject::update();
        this->draw(this->getBlank()->getManager<SceneManager>()->getScene()->getShader());
	}
}