//
// Created by unkorunk on 17.02.2020.
//

#pragma once

#include <exception>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <memory>

#include <freetype/ftbitmap.h>

#include "UIComponent.h"
#include "Font.h"
#include "Texture.h"

namespace GUI {
    class Label : public UIComponent {
    public:
        Label();

        virtual ~Label();

        void draw(Shader *shader) override;

        void setFont(Font *font);

        Font *getFont() const;

        void setText(const std::string &text);

        std::string getText() const;

        void setWidth(float width);
        void setHeight(float height);
        void setSize(const Vector2f& size);

    private:
        std::unique_ptr<Texture> texture;

        std::string text;
        Font *font;
    };
}
