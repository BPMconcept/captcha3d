#include "captcha3d.h"
#include "zbuffer.h"
#include "data.h"
#include "font.h"
#include "transformations.h"

#include <opencv/cv.h>

static Letter descriptionLettre(char c);

void captcha3d_generate(struct captcha3d_image *image, const char *string, struct captcha3d_color couleur)
{
    CvMat* buffer = cvCreateMat(image->width, image->height, CV_32FC1);
    cvZero(buffer);

    int i;
    Material materiau = {couleur, 0.3, 0.9, 30};

    //Paramètres pour le placement des lettres dans l'espace
    float z, e, offset;
    int marge;

    //Obtention des paramètres pour le placement des lettres dans l'espace
    parametresTransformation(&z, &marge, &e, &offset, image->height, image->width, strlen(string));

    //Sélection d'un matériau aléatoire pour la lettre
    //materiau=selectionMateriau();

    //Pour chaque lettre de la chaine de caractère
    for (i = 0; i < strlen(string); i++) {
        // Chargement de la lettre
        Letter lettre = descriptionLettre(string[i]);

        //Transformation de la lettre
        lettre = transformation(lettre, i, image->width, image->height, z, marge, e, offset);

        zBufferGouraud(image, buffer, lettre, materiau);
    }
}

/**
 * \fn Lettre descriptionLettre(char c)
 * \brief Fonction qui renvoie la description d'une lettre à partir d'un caractère
 *
 * \param c Charactère dont on veut la description
 */
Letter descriptionLettre(char c)
{
    switch (c) {
    case '9':
        return arial[0];
        break;
    case '8':
        return arial[1];
        break;
    case '7':
        return arial[2];
        break;
    case '6':
        return arial[3];
        break;
    case '5':
        return arial[4];
        break;
    case '4':
        return arial[5];
        break;
    case '3':
        return arial[6];
        break;
    case '2':
        return arial[7];
        break;
    case '1':
        return arial[8];
        break;
    case '0':
        return arial[9];
        break;
    case 'z':
        return arial[10];
        break;
    case 'y':
        return arial[11];
        break;
    case 'x':
        return arial[12];
        break;
    case 'w':
        return arial[13];
        break;
    case 'v':
        return arial[14];
        break;
    case 'u':
        return arial[15];
        break;
    case 't':
        return arial[16];
        break;
    case 's':
        return arial[17];
        break;
    case 'r':
        return arial[18];
        break;
    case 'q':
        return arial[19];
        break;
    case 'p':
        return arial[20];
        break;
    case 'o':
        return arial[21];
        break;
    case 'n':
        return arial[22];
        break;
    case 'm':
        return arial[23];
        break;
    case 'l':
        return arial[24];
        break;
    case 'k':
        return arial[25];
        break;
    case 'j':
        return arial[26];
        break;
    case 'i':
        return arial[27];
        break;
    case 'h':
        return arial[28];
        break;
    case 'g':
        return arial[29];
        break;
    case 'f':
        return arial[30];
        break;
    case 'e':
        return arial[31];
        break;
    case 'd':
        return arial[32];
        break;
    case 'c':
        return arial[33];
        break;
    case 'b':
        return arial[34];
        break;
    case 'a':
        return arial[35];
        break;
    default:
        return arial[36];
    }
}
