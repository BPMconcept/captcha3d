#ifndef CAPTCHA_3D_H
#define CAPTCHA_3D_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

struct captcha3d_config {
    char *string;
    char *file;
    size_t width;
    size_t height;
    size_t aliasing;
};

struct captcha3d_pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct captcha3d_image {
    size_t width;
    size_t height;
    struct captcha3d_pixel data[];
};

static inline struct captcha3d_pixel* captcha3d_image_get(struct captcha3d_image *image, size_t w, size_t h)
{
    assert(w < image->width);
    assert(h < image->height);

    const size_t offset = image->height * w + h;
    return image->data + offset;
}

struct captcha3d_image* captcha3d_image_init(size_t width, size_t height);
void captcha3d_image_fill(struct captcha3d_image *image, struct captcha3d_pixel color);
void captcha3d_image_release(struct captcha3d_image *image);

void captcha3d_generate(struct captcha3d_image *image, const char *string, struct captcha3d_pixel couleur);

#endif
