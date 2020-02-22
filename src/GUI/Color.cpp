//
// Created by unkorunk on 20.02.2020.
//

#include "Color.h"

namespace GUI {
    Color::Color()
            : red(), green(), blue(), alpha(255) {}

    Color::Color(uint8_t red, uint8_t green, uint8_t blue)
            : red(red), green(green), blue(blue), alpha(255) {}

    Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            : red(red), green(green), blue(blue), alpha(alpha) {}
}