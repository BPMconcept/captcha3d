#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

struct captcha3d_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct captcha3d_color random_color();

#endif
