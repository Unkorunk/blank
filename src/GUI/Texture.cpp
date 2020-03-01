//
// Created by unkorunk on 20.02.2020.
//

#include "Texture.h"

namespace GUI {
    Texture::Texture() : cols(), rows(), buffer(), texture_id() {
        glGenTextures(1, &this->texture_id);
    }

    Texture::Texture(GLsizei cols, GLsizei rows)
            : cols(cols), rows(rows), buffer(new uint8_t[4 * cols * rows]()), texture_id() {
        glGenTextures(1, &this->texture_id);
        this->refresh();
    }

    GUI::Texture::Texture(GLsizei cols, GLsizei rows, const uint8_t *buffer)
            : cols(cols), rows(rows), buffer(new uint8_t[4 * cols * rows]), texture_id() {
        std::copy(buffer, buffer + 4 * cols * rows, this->buffer.get());
        glGenTextures(1, &this->texture_id);
        this->refresh();
    }

    GUI::Texture::~Texture() {
        glDeleteTextures(1, &texture_id);
    }

    void GUI::Texture::draw(Shader *shader) {
        if (!buffer) return;
        Component::draw(shader);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        std::array<GLfloat, 6 * 3> vertices = {
                this->getX(), this->getY(), 0.0f,
                this->getX(), this->getY() - this->getHeight(), 0.0f,
                this->getX() + this->getWidth(), this->getY(), 0.0f,

                this->getX() + this->getWidth(), this->getY(), 0.0f,
                this->getX(), this->getY() - this->getHeight(), 0.0f,
                this->getX() + this->getWidth(), this->getY() - this->getHeight(), 0.0f
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

    void Texture::setPixel(size_t x, size_t y, Color color) {
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

    Color Texture::getPixel(size_t x, size_t y) const {
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
