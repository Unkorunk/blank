//
// Created by unkorunk on 20.02.2020.
//

#ifndef BLANK_GAME_COLOR_H
#define BLANK_GAME_COLOR_H

#include <cstdint>

namespace GUI {
    class Color {
    public:
        Color();

        Color(uint8_t red, uint8_t green, uint8_t blue);

        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        uint8_t red, green, blue, alpha;

    private:
    };
}

#endif //BLANK_GAME_COLOR_H
