#ifndef PARAM_H_INCLUDED
#define PARAM_H_INCLUDED

#include <stddef.h>
#include <opencv/cv.h>

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

// Variables globales
//char *cfg_str;
//char *cfg_output;
//int cfg_width;
//int cfg_height;
int cfg_window;
int cfg_deform_sin;
int cfg_degrade;
//float cfg_aliasing;
CvScalar cfg_background;

int checkParams(int argc, char *argv[]);
void initGlobalParams();
int checkChar(char *string);

#endif // PARAM_H_INCLUDED
