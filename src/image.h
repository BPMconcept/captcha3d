#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "color.h"

struct captcha3d_image {
    size_t width;
    size_t height;
    struct captcha3d_color data[];
};

static inline struct captcha3d_color* captcha3d_image_get(struct captcha3d_image *image, size_t w, size_t h)
{
    assert(w < image->width);
    assert(h < image->height);

    const size_t offset = image->height * w + h;
    return image->data + offset;
}

struct captcha3d_image* captcha3d_image_init(size_t width, size_t height);
void captcha3d_image_fill(struct captcha3d_image *image, struct captcha3d_color color);
void captcha3d_image_release(struct captcha3d_image *image);

#endif
