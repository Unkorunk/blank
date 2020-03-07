//
// Created by unkorunk on 13.02.2020.
//

#pragma once

#include <string>
#include <array>

#include <GL/glew.h>

#include "GameObject/GameObject.h"
#include "Settings.h"
#include "Shader.h"
#include "Utility/Vector2f.h"
#include "Component/Transform.h"

namespace GUI {
    class UIComponent : public GameObject {
    public:
        UIComponent();
        virtual ~UIComponent() = default;

        virtual void draw(Shader* shader);
        void update() override;

    protected:
        std::unique_ptr<Component::Transform> transform;

    };
}
