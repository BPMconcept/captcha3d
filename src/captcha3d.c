#include <string.h>

#include "captcha3d.h"
#include "zbuffer.h"
#include "data.h"
#include "font.h"
#include "transformations.h"
#include "illumination.h"
#include "file.h"

void captcha3d_generate(struct Configuration *config)
{
    struct Image *image = captcha3d_image_allocate(config->width, config->height);
    struct zBufferData *buffer = z_buffer_data_allocate(image);

    struct Color background = {255, 255, 255, 255};
    captcha3d_image_fill(image, background);

    int i;
    Material materiau = {random_color(), 0.3, 0.9, 30};

    //Paramètres pour le placement des lettres dans l'espace
    float z, e, offset;
    int marge;

    //Obtention des paramètres pour le placement des lettres dans l'espace
    parametresTransformation(&z, &marge, &e, &offset, image->height, image->width, strlen(config->string));

    //Sélection d'un matériau aléatoire pour la lettre
    //materiau=selectionMateriau();

    for (i = 0; i < strlen(config->string); i++) {
        // Copy a new letter from the given template
        Letter letter = *get_letter(FONT_ARIAL, config->string[i]);

        // Apply transformations
        letter_transform(&letter, i, image->width, image->height, z, marge, e, offset);

        // Run the Z-buffer algorithm
        z_buffer_run(buffer, &letter, materiau);
    }

    // Save the image
    save_png(config, image);

    // Release structures
    z_buffer_data_release(buffer);
    captcha3d_image_release(image);
}

