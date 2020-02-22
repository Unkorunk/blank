//
// Created by unkorunk on 20.02.2020.
//

#ifndef BLANK_GAME_TEXTURE_H
#define BLANK_GAME_TEXTURE_H

#include <algorithm>
#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>
#include <array>

#include "Component.h"
#include "Color.h"

namespace GUI {
    class Texture : public Component {
    public:
        Texture();
        Texture(GLsizei cols, GLsizei rows);
        Texture(GLsizei cols, GLsizei rows, const uint8_t *buffer);

        void setData(GLsizei cols, GLsizei rows, const uint8_t *buffer);

        GLsizei getCols() const;
        GLsizei getRows() const;

        void setPixel(size_t x, size_t y, Color color);
        Color getPixel(size_t x, size_t y) const;

        virtual ~Texture();

        void draw(Shader *shader) override;

    private:
        void refresh();
        GLuint texture_id;

        std::unique_ptr<uint8_t[]> buffer;
        GLsizei cols, rows;
    };
}


#endif //BLANK_GAME_TEXTURE_H
