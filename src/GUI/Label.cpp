//
// Created by unkorunk on 17.02.2020.
//

#include "Label.h"

namespace GUI {
    Label::Label() : text(), font(nullptr), texture(new Texture()) {
        this->addChild(texture.get());
    }

    Label::~Label() = default;

    void Label::draw(Shader* shader) {
        UIComponent::draw(shader);

        if (font == nullptr || text.empty()) {
            return;
        }

        texture->draw(shader);
    }

    void Label::setText(const std::string &text) {
        this->text = text;

        unsigned int texture_width = 0, texture_height = 0;

        FT_Int max_bitmap_top = 0;

        for (char c : this->text) {
            FT_GlyphSlot glyph = font->getGlyph(c);
            texture_width += (glyph->advance.x >> 6);
            texture_height = std::max(texture_height, glyph->bitmap.rows);
            max_bitmap_top = std::max(max_bitmap_top, glyph->bitmap_top);
        }

        std::unique_ptr<unsigned char[]> buffer(new unsigned char[4 * texture_height * texture_width]());

        unsigned int offset_x = 0;

        for (char c : this->text) {
            FT_GlyphSlot glyph = font->getGlyph(c);
            FT_Bitmap bitmap;
            FT_Bitmap_Init(&bitmap);
            FT_Error error = FT_Bitmap_Convert(Font::getLibrary(), &glyph->bitmap, &bitmap, 1);
            if (error) {
                throw std::runtime_error("Failed bitmap convert. Error code: " + std::to_string(error));
            }

            if (bitmap.pixel_mode != FT_PIXEL_MODE_GRAY) {
                throw std::runtime_error("Incorrect pixel mode");
            } else if (glyph->format != FT_GLYPH_FORMAT_BITMAP) {
                throw std::runtime_error("Glyph format isn't bitmap");
            } else if (glyph->num_subglyphs != 0) {
                throw std::runtime_error("Glyph have subglyphs");
            } else if (glyph->next != nullptr) {
                throw std::runtime_error("Glyph have next glyph");
            } else if (bitmap.pitch < 0) {
                throw std::runtime_error("Pitch is negative");
            }

            for (unsigned int y = 0; y < bitmap.rows; y++) {
                for (unsigned int x = 0; x < bitmap.width; x++) {
                    unsigned int pixel_index = 4 * (texture_width *
                                                    (texture_height - 1 - y - (max_bitmap_top - glyph->bitmap_top)) +
                                                    x + offset_x + glyph->bitmap_left);
                    unsigned char gray = bitmap.buffer[bitmap.pitch * y + x];

                    if (pixel_index + 3 < 4 * texture_height * texture_width) {
                        buffer[pixel_index + 0] = gray;
                        buffer[pixel_index + 1] = gray;
                        buffer[pixel_index + 2] = gray;
                        buffer[pixel_index + 3] = gray;
                    }
                }
            }

            offset_x += (glyph->advance.x >> 6);

            FT_Bitmap_Done(Font::getLibrary(), &bitmap);
        }

        texture->setData(texture_width, texture_height, buffer.get());

        this->setHeight(transform->getHeight());
    }

    std::string Label::getText() const {
        return this->text;
    }

    void Label::setFont(Font *font) {
        this->font = font;
    }

    Font *Label::getFont() const {
        return this->font;
    }

    void Label::setWidth(float width) {
        transform->setWidth(width);
        transform->setHeight(
            static_cast<float>(texture->getRows()) * transform->getWidth() / static_cast<float>(texture->getCols()) * ratio
        );
    }

    void Label::setHeight(float height) {
        transform->setHeight(height);
        transform->setWidth(
            static_cast<float>(texture->getCols()) * transform->getHeight() / static_cast<float>(texture->getRows()) * (1.0f / ratio)
        );
    }

    void Label::setSize(const Vector2f& size) {
        transform->setWidth(size.getX());
    }

    void Label::setRatio(float ratio) {
        this->ratio = ratio;
    }

    float Label::getRatio() const {
        return this->ratio;
    }
}
