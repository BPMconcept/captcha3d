#include "image.h"

struct captcha3d_image* captcha3d_image_init(size_t width, size_t height)
{
    struct captcha3d_image *image = malloc(sizeof(struct captcha3d_image) + (width * height * sizeof(struct captcha3d_color)));

    image->width = width;
    image->height = height;

    return image;
}

void captcha3d_image_release(struct captcha3d_image *image)
{
    free(image);
}

void captcha3d_image_fill(struct captcha3d_image *image, struct captcha3d_color color)
{
    for (int x = 0; x < image->width; ++x) {
        for (int y = 0; y < image->height; ++y) {
            struct captcha3d_color *pixel = captcha3d_image_get(image, x, y);
            pixel->red = color.red;
            pixel->green = color.green;
            pixel->blue = color.blue;
            pixel->alpha = color.alpha;
        }
    }
}
