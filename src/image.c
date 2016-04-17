#include "image.h"

struct Image* captcha3d_image_allocate(size_t width, size_t height)
{
    struct Image *image = malloc(sizeof(struct Image) + (width * height * sizeof(struct Color)));

    image->width = width;
    image->height = height;

    return image;
}

void captcha3d_image_release(struct Image *image)
{
    free(image);
}

void captcha3d_image_fill(struct Image *image, struct Color color)
{
    for (int x = 0; x < image->width; ++x) {
        for (int y = 0; y < image->height; ++y) {
            struct Color *pixel = captcha3d_image_get(image, x, y);
            pixel->red = color.red;
            pixel->green = color.green;
            pixel->blue = color.blue;
            pixel->alpha = color.alpha;
        }
    }
}
