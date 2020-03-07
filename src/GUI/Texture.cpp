//
// Created by unkorunk on 20.02.2020.
//

#include "Texture.h"

namespace GUI {
    Texture::Texture() : texture_id(), buffer(), rows(), cols() {
        glGenTextures(1, &this->texture_id);
    }

    Texture::Texture(GLsizei cols, GLsizei rows)
            : texture_id(), buffer(new uint8_t[4 * cols * rows]()), rows(rows), cols(cols) {
        glGenTextures(1, &this->texture_id);
        this->refresh();
    }

    Texture::Texture(GLsizei cols, GLsizei rows, const uint8_t *buffer)
            : texture_id(), buffer(new uint8_t[4 * cols * rows]), rows(rows), cols(cols) {
        std::copy(buffer, buffer + 4 * cols * rows, this->buffer.get());
        glGenTextures(1, &this->texture_id);
        this->refresh();
    }

    Texture::~Texture() {
        glDeleteTextures(1, &texture_id);
    }

    void Texture::draw(Shader *shader) {
        if (!buffer) return;
        UIComponent::draw(shader);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        std::array<GLfloat, 6 * 3> vertices = {
                transform->getX(), transform->getY(), 0.0f,
                transform->getX(), transform->getY() - transform->getHeight(), 0.0f,
                transform->getX() + transform->getWidth(), transform->getY(), 0.0f,

                transform->getX() + transform->getWidth(), transform->getY(), 0.0f,
                transform->getX(), transform->getY() - transform->getHeight(), 0.0f,
                transform->getX() + transform->getWidth(), transform->getY() - transform->getHeight(), 0.0f
        };

        std::array<GLfloat, 6 * 2> uvs = {
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 1.0f,
                1.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        };

        shader->set("use_texture", 1);
        shader->set("m_sampler", 0);
        shader->set(0, vertices.size() * sizeof(GLfloat), 3, vertices.data());
        shader->set(1, uvs.size() * sizeof(GLfloat), 2, uvs.data());

        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
    }

    void Texture::setPixel(GLsizei x, GLsizei y, Color color) {
        if (x >= this->cols || y >= this->rows) {
            throw std::out_of_range("Out of range");
        }
        size_t offset = 4 * (y * this->cols + x);
        this->buffer[offset + 0] = color.blue;
        this->buffer[offset + 1] = color.green;
        this->buffer[offset + 2] = color.red;
        this->buffer[offset + 3] = color.alpha;

        this->refresh();
    }

    Color Texture::getPixel(GLsizei x, GLsizei y) const {
        if (x >= this->cols || y >= this->rows) {
            throw std::out_of_range("Out of range");
        }
        size_t offset = 4 * (y * this->cols + x);
        return Color(this->buffer[offset + 2], this->buffer[offset + 1], this->buffer[offset + 0],
                     this->buffer[offset + 3]);
    }

    void Texture::refresh() {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->cols, this->rows, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                     this->buffer.get());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    void Texture::setData(GLsizei cols, GLsizei rows, const uint8_t *buffer) {
        this->cols = cols;
        this->rows = rows;
        this->buffer = std::make_unique<uint8_t[]>(4 * cols * rows);
        std::copy(buffer, buffer + 4 * cols * rows, this->buffer.get());

        this->refresh();
    }

    GLsizei Texture::getCols() const {
        return this->cols;
    }

    GLsizei Texture::getRows() const {
        return this->rows;
    }
}
