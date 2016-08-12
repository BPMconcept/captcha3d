#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "data.h"
#include "transformations.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * \fn void parametresTransformation(float *z,int *marge,float *e, float *offset,int height, int width,int nbLettres)
 * \brief Calcul divers paramètres de transformation des lettres
 *
 * \param z Profondeur où placer les lettres
 * \param marge Marge sur les bords horizontaux de l'image
 * \param e Echelle des lettres
 * \param offset Distance entre chaque lettre
 * \param height Hauteur de l'image
 * \param width Largeur de l'image
 * \param nbLettres Nombre de lettres à afficher
 *
 */
void parametresTransformation(float *z, int *marge, float *e, float *offset, int height, int width, int nbLettres)
{
    //Profondeur où sera placée la lettre
    *z = height * 6.9;
    //Marge horizontale par rapport aux bords
    *marge = (int) height * 0.8 * 1.2 / 2 + 10 * width / 400;
    //Echelle de grandeur de la lettre
    *e = (float) (Z_PROJECTION_CENTER + (*z)) / Z_PROJECTION_CENTER * height * 0.8 / 2. / 6.;
    //Offset entre chaque lettre
    *offset = (float) ((width - 2 * (*marge)) / (nbLettres - 1)) * (Z_PROJECTION_CENTER + fabs(*z)) / Z_PROJECTION_CENTER;
}



/**
 * \fn CvPoint3D32f barycentre(Lettre lettre)
 * \brief Calcul le barycentre d'une lettre
 *
 * \param lettre Lettre dont il faut calculter le barycentre
 *
 * \return Barycentre (point de l'espace 3d)
 */
//Vector3d barycentre(Letter lettre)
//{
//    int i;
//    Vector3d barycentre = {0, 0, 0};

//    for (i = 0; i < lettre.pointsNumber; i++) {
//        barycentre.x += lettre.points[i].x;
//        barycentre.y += lettre.points[i].y;
//        barycentre.z += lettre.points[i].z;
//    }

//    barycentre.x /= lettre.pointsNumber;
//    barycentre.y /= lettre.pointsNumber;
//    barycentre.z /= lettre.pointsNumber;

//    return barycentre;
//}

/**
 * \fn Lettre deformation(Lettre lettre)
 * \brief Fonction qui déforme une lettre en modifiant la position de ses points aléatoirement
 *
 * \param lettre Lettre à déformer
 *
 * \return Lettre déformée
 */
Letter deformation(Letter lettre)
{
    float offset, coeff = 1;
    int i;
    unsigned int b;
    Vector3d p;

    for (i = 0; i < lettre.pointsNumber; i++) {
        b = rand () % 2;
        p = lettre.points[i];

        if (b) {
            offset = ((rand () * 1.0) / RAND_MAX) * coeff;
            p.x += offset;

            offset = ((rand () * 1.0) / RAND_MAX) * coeff;
            p.y += offset;

            lettre.points[i] = p;
        }
    }

    return lettre;
}

/**
 * \fn Lettre deformation_sin(Lettre lettre, char type)
 * \brief Fonction qui déforme une lettre en modifiant la position de ses points suivant une sinusoïde
 *
 * \param lettre Lettre à déformer
 * \param type Choix déformation horizontale ou verticale
 *
 * \return Lettre déformée
 */
Letter deformation_sin(Letter lettre, char type)
{
    int i;
    Vector3d p;

    for (i = 0; i < lettre.pointsNumber; i++) {
        p = lettre.points[i];

        if (type == 'v') {
            p.y += DEFORMATION_SIN_AMPLITUDE * sin((2 * M_PI) / DEFORMATION_SIN_PERIOD * p.x);
        } else {
            p.x += DEFORMATION_SIN_AMPLITUDE * sin((2 * M_PI) / DEFORMATION_SIN_PERIOD * p.y);
        }

        lettre.points[i] = p;
    }

    return lettre;
}

