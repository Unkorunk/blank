//
// Created by unkorunk on 20.02.2020.
//

#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>
#include <array>

#include "UIComponent.h"
#include "Color.h"

namespace GUI {
    class Texture : public UIComponent {
    public:
        Texture();
        Texture(GLsizei cols, GLsizei rows);
        Texture(GLsizei cols, GLsizei rows, const uint8_t *buffer);

        void setData(GLsizei cols, GLsizei rows, const uint8_t *buffer);

        GLsizei getCols() const;
        GLsizei getRows() const;

        void setPixel(GLsizei x, GLsizei y, Color color);
        Color getPixel(GLsizei x, GLsizei y) const;

        virtual ~Texture();

        void draw(Shader *shader) override;

    private:
        void refresh();
        GLuint texture_id;

        std::unique_ptr<uint8_t[]> buffer;
        GLsizei rows, cols;
    };
}
