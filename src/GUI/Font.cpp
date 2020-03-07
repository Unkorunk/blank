//
// Created by unkorunk on 17.02.2020.
//

#include "Font.h"

namespace GUI {
    Font *Font::loadFont(const std::string &filename) {
        Font* font = new Font();
        
        FT_Error error = FT_New_Face(getLibrary(), filename.c_str(), 0, &font->face);
        if (error == FT_Err_Unknown_File_Format) {
            throw std::runtime_error("Unknown font file format");
        } else if (error) {
            throw std::runtime_error("Failed create new face");
        }

        font->setPixelSizes(0, 16);

        return font;
    }

    void Font::setPixelSizes(FT_UInt width, FT_UInt height) {
        FT_Error error = FT_Set_Pixel_Sizes(this->face, width, height);
        if (error) {
            throw std::runtime_error("Failed set pixel sizes");
        }
    }

    void Font::setCharSize(FT_F26Dot6 char_width, FT_F26Dot6 char_height, FT_UInt h_resolution, FT_UInt v_resolution) {
        FT_Error error = FT_Set_Char_Size(this->face, char_width, char_height, h_resolution, v_resolution);
        if (error) {
            throw std::runtime_error("Failed set char size");
        }
    }

    FT_GlyphSlot Font::getGlyph(FT_ULong symbol) {
        FT_UInt glyph_index = FT_Get_Char_Index(this->face, symbol);

        FT_Error error = FT_Load_Glyph(this->face, glyph_index, FT_LOAD_DEFAULT);
        if (error == FT_Err_Invalid_Argument) {
            throw std::runtime_error("Failed load glyph. Invalid argument.");
        } else if (error == FT_Err_Glyph_Too_Big) {
            throw std::runtime_error("Failed load glyph. Glyph too big.");
        } else if (error == FT_Err_Invalid_Size_Handle) {
            throw std::runtime_error("Failed load glyph. Invalid size handle. Maybe, you not set char size.");
        } else if (error) {
            throw std::runtime_error("Failed load glyph. Error code: " + std::to_string(error));
        }

        error = FT_Render_Glyph(this->face->glyph, FT_RENDER_MODE_NORMAL);
        if (error) {
            throw std::runtime_error("Failed render glyph");
        }

        return this->face->glyph;
    }

    Font::~Font() {
        FT_Done_Face(face);
    }

    FT_Library Font::getLibrary() {
        static bool initialized = false;
        static FT_Library library;
        if (!initialized) {
            initialized = true;

            FT_Error error = FT_Init_FreeType(&library);
            if (error) {
                throw std::runtime_error("Failed load FreeType library");
            }

            // TODO: make FT_Done_FreeType(library);
        }
        return library;
    }

}
