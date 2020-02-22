//
// Created by unkorunk on 17.02.2020.
//

#ifndef BLANK_GAME_FONT_H
#define BLANK_GAME_FONT_H

#include <string>
#include <iostream>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace GUI {
    class Font {
    public:
        static Font* loadFont(const std::string& filename);
        static FT_Library getLibrary();

        virtual ~Font();

        void setCharSize(FT_F26Dot6 char_width, FT_F26Dot6 char_height, FT_UInt h_resolution, FT_UInt v_resolution);
        void setPixelSizes(FT_UInt width, FT_UInt height);

        FT_GlyphSlot getGlyph(FT_ULong symbol);

    private:
        Font() = default;
        FT_Face face;
    };
}

#endif //BLANK_GAME_FONT_H
