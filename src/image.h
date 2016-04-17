#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "color.h"

struct Image {
    size_t width;
    size_t height;
    struct Color data[];
};

/**
 * @brief Allocate a Captcha3D image structure.
 * @param width     Image width
 * @param height    Image height
 * @return Image resource
 */
struct Image* captcha3d_image_allocate(size_t width, size_t height);

/**
 * @brief Fill an image with the given color.
 * @param image     Image resource
 * @param color     Color to use
 */
void captcha3d_image_fill(struct Image *image, struct Color color);

/**
 * @brief Deallocate a Captcha3D image structure.
 * @param image     Image resource
 */
void captcha3d_image_release(struct Image *image);

/**
 * @brief Get a color structure at a given image position.
 * @param image     Image resource
 * @param w         X position (width)
 * @param h         Y position (height)
 * @return A readable/writable color structure
 */
static inline struct Color* captcha3d_image_get(struct Image *image, size_t w, size_t h)
{
    assert(w < image->width);
    assert(h < image->height);

    const size_t offset = image->height * w + h;
    return image->data + offset;
}

#endif
