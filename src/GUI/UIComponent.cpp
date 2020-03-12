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
            std::array<GLfloat, 8 * 3> vertices = {
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f
            };
            std::array<GLfloat, 8 * 4> colors = {};
            for (size_t i = 0; i < 8; i++) {
                colors[4 * i + 0] = 1.0f;
                colors[4 * i + 1] = 0.0f;
                colors[4 * i + 2] = 0.0f;
                colors[4 * i + 3] = 1.0f;
            }
            std::array<GLfloat, 8 * 2> uvs = {};

            shader->set("use_texture", 0);
            shader->set("MVP", this->transform->getModelMatrix());
            shader->set(0, vertices.size() * sizeof(GLfloat), 3, vertices.data());
            shader->set(1, uvs.size() * sizeof(GLfloat), 2, uvs.data());
            shader->set(2, colors.size() * sizeof(GLfloat), 4, colors.data());

            glDrawArrays(GL_LINES, 0, 2 * 4);
        }
    }

	void UIComponent::update()
	{
        GameObject::update();
        this->draw(this->getBlank()->getManager<SceneManager>()->getScene()->getShader());
	}
}