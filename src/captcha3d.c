#include "captcha3d.h"
#include "zbuffer.h"
#include "data.h"
#include "font.h"
#include "transformations.h"
#include "illumination.h"
#include "file.h"

#include <opencv/cv.h>

static Letter descriptionLettre(char c);

void captcha3d_generate(struct captcha3d_config *config)
{
    struct captcha3d_image *image = captcha3d_image_init(config->width, config->height);

    struct captcha3d_color background = {255, 255, 255, 255};
    captcha3d_image_fill(image, background);

    CvMat* buffer = cvCreateMat(image->width, image->height, CV_32FC1);
    cvZero(buffer);

    int i;
    Material materiau = {randomColor(), 0.3, 0.9, 30};

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
        z_buffer(image, buffer, &letter, materiau);
    }

    save_png(config, image);
    captcha3d_image_release(image);
}

/**
 * \fn Lettre descriptionLettre(char c)
 * \brief Fonction qui renvoie la description d'une lettre à partir d'un caractère
 *
 * \param c Charactère dont on veut la description
 */
Letter descriptionLettre(char c)
{

}
