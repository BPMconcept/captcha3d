#include <string.h>
#include <math.h>

#include "captcha3d.h"
#include "zbuffer.h"
#include "data.h"
#include "font.h"
#include "illumination.h"
#include "file.h"

static void initialize_transform(float *z, int *marge, float *e, float *offset, int height, int width, int lettersNumber)
{
    // Letter depth
    *z = height * 6.9;

    // Horizontal margin
    *marge = (int) height * 0.8 * 1.2 / 2 + 10 * width / 400;

    // Letter scale
    *e = (float) (Z_PROJECTION_CENTER + (*z)) / Z_PROJECTION_CENTER * height * 0.8 / 2. / 6.;

    // Letter padding
    *offset = (float) ((width - 2 * (*marge)) / (lettersNumber - 1)) * (Z_PROJECTION_CENTER + fabs(*z)) / Z_PROJECTION_CENTER;
}

void captcha3d_generate(struct Configuration *config)
{
    // Create a new image
    struct Image *image = captcha3d_image_allocate(config->width, config->height);
    captcha3d_image_fill(image, config->background);

    // Seed random engine
    srand(config->seed);

    // Random texture
    Material material = {color_random(), 0.3, 0.9, 30};

    // Initialize spatial positionning
    float z, e, offset;
    int margin;
    initialize_transform(&z, &margin, &e, &offset, image->height, image->width, strlen(config->string));

    #pragma omp parallel for
    for (size_t i = 0; i < strlen(config->string); i++) {
        // Copy a new letter from the given template
        Letter letter = *get_letter(FONT_ARIAL, config->string[i]);

        // Apply transformations
        letter_transform(&letter, i, image->width, image->height, z, margin, e, offset);

        // Run the Z-buffer algorithm
        struct zBufferData *buffer = z_buffer_data_allocate(image);
        z_buffer_run(buffer, &letter, material);
        z_buffer_data_release(buffer);
    }

    // Save the image
    save_png(config, image);

    // Release structure
    captcha3d_image_release(image);
}

