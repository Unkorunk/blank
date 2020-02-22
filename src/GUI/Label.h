//
// Created by unkorunk on 17.02.2020.
//

#ifndef BLANK_GAME_LABEL_H
#define BLANK_GAME_LABEL_H

#include <exception>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <memory>

#include <freetype/ftbitmap.h>

#include "Component.h"
#include "Font.h"
#include "Texture.h"

namespace GUI {
    class Label : public Component {
    public:
        Label();

        virtual ~Label();

        void draw(Shader *shader) override;

        void setFont(Font *font);

        Font *getFont() const;

        void setText(const std::string &text);

        std::string getText() const;

    private:
        Texture texture;

        std::string text;
        Font *font;
    };
}

#endif //BLANK_GAME_LABEL_H
