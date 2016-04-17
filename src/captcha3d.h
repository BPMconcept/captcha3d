#ifndef CAPTCHA_3D_H
#define CAPTCHA_3D_H

#include "image.h"

struct captcha3d_config {
    char *string;
    char *file;
    size_t width;
    size_t height;
    size_t aliasing;
};

void captcha3d_generate(struct captcha3d_config *config);

#endif
