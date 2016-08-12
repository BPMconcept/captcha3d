#include <string.h>

#include "image.h"

struct Image* captcha3d_image_allocate(size_t width, size_t height)
{
    struct Image *image = malloc(sizeof(struct Image) + (width * height * sizeof(struct Color)));

    image->width = width;
    image->height = height;

    return image;
}

void captcha3d_image_reset(struct Image *image)
{
    memset(image->data, 255, sizeof(struct Color) * image->width * image->height);
}

void captcha3d_image_fill(struct Image *image, struct Color color)
{
    struct Color *pointer = image->data;

    for (size_t x = 0; x < image->width; ++x) {
        for (size_t y = 0; y < image->height; ++y) {
            *pointer++ = color;
        }
    }
}

void captcha3d_image_release(struct Image *image)
{
    free(image);
}
