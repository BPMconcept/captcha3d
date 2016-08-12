#ifndef CAPTCHA_3D_H
#define CAPTCHA_3D_H

#include "image.h"

struct Configuration {
    char *string;
    char *file;
    size_t width;
    size_t height;
    size_t aliasing;
    struct Color background;
};

/**
 * @brief Generate a captcha according to the given configuration.
 * @param config    A configuration set
 */
void captcha3d_generate(struct Configuration *config);

#endif
