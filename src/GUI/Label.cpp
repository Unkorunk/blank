//
// Created by unkorunk on 17.02.2020.
//

#include "Label.h"

namespace GUI {
    Label::Label() : text(), font(nullptr) {}

    Label::~Label() = default;

    void Label::draw(Shader* shader) {
        if (font == nullptr || text.empty()) {
            return;
        }

        texture.setX(this->getX());
        texture.setY(this->getY());
        texture.setWidth(this->getWidth());
        texture.setHeight(this->getHeight());

        texture.draw(shader);
    }

    void Label::setText(const std::string &text) {
        this->text = text;

        unsigned int texture_width = 0, texture_height = 0;

        FT_Int max_bitmap_top = 0;

        for (char c : this->text) {
            FT_GlyphSlot glyph = font->getGlyph(c);
            texture_width += (glyph->advance.x >> 6);
            texture_height = std::max(texture_height, glyph->bitmap_top + glyph->bitmap.rows);
            max_bitmap_top = std::max(max_bitmap_top, glyph->bitmap_top);
        }

        this->setWidth(1.0f);
        this->setHeight(static_cast<float>(texture_height) / static_cast<float>(texture_width));

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
            } else if (bitmap.width != bitmap.pitch) {
                throw std::runtime_error("Alignment not equal 1");
            }

            for (unsigned int y = 0; y < bitmap.rows; y++) {
                for (unsigned int x = 0; x < bitmap.width; x++) {
                    unsigned int pixel_index = 4 * (texture_width *
                                                    (texture_height - 1 - y - (max_bitmap_top - glyph->bitmap_top)) +
                                                    x + offset_x + glyph->bitmap_left);
                    unsigned char gray = bitmap.buffer[bitmap.pitch * y + x];

                    if (pixel_index < 4 * texture_height * texture_width) {
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

        texture.setData(texture_width, texture_height, buffer.get());
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
}
