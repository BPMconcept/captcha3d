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
 * \fn Lettre transformation(Lettre lettre, int i, int width, int height,int z,int marge,float e, float offset)
 * \brief Transforme une lettre : échelle, rotation, translation adéquates
 *
 * \param lettre Letter originale à transformer
 * \param i Numéro de la lettre à afficher
 * \param width Largeur de l'image
 * \param height Hauteur de l'image
 * \param z Profondeur où placer les lettres
 * \param marge Marge sur les bords horizontaux
 * \param e Echelle de la transformation
 * \param offset Distance entre chaque lettre
 *
 * \return Lettre transformée
 */
void letter_transform(Letter *letter, int i, int width, int height, int z, int marge, float e, float offset)
{
    Vector3d translate;
    float angle1, angle2, angle3;

//    // Déformation
//    if (cfg_deform_sin) {
//        lettre = deformation_sin(lettre, 'h');
//    }

    // Mise à l'échelle de la lettre
    scale(letter, e) ;

    // Rotation de la lettre
    angle1 = (float) 1.5 * rand() / RAND_MAX - 0.75;
    angle2 = (float) 1.5 * rand() / RAND_MAX - 0.75;
    angle3 = (float) 1.5 * rand() / RAND_MAX - 0.75;

    //Rotation aléatoire
    Vector3d angles = {angle1, angle2, angle3} ;
    letter_rotate(letter, angles);

    // Translation de la lettre
    translate = calculterTranslation(width, height, marge, z);

    //On décale la lettre de i fois le offset
    translate.x += offset * i;
    letter_translate(letter, translate);
}

/**
 * \fn Vecteur calculterTranslation(int width, int height,int marge,float z)
 * \brief Calcul le vecteur de translation pour bien placer la lettre dans l'espace
 *
 * \param width Largeur de l'image
 * \param height Hauteur de l'image
 * \param marge Marge sur les bords horizontaux
 * \param z Profondeur où placer les lettres
 *
 * \return Vecteur de translation
 */
Vector3d calculterTranslation(int width, int height, int marge, float z)
{
    Vector3d translate;

    translate.x = calculOffsetX(z, width, marge);
    translate.y = height / 2;
    translate.z = z;

    return translate;
}

/**
 * \fn float calculOffsetX(float z,int width, int marge)
 * \brief Calcul la distance entre deux lettres dans l'espace
 *
 * \param z Profondeur où sont placées les lettres
 * \param width Largeur de l'image
 * \param height Hauteur de l'image
 *
 * \return Offset
 */
float calculOffsetX(float z, int width, int marge)
{
    return (float) width / 2 - (fabs(z) + Z_PROJECTION_CENTER) / Z_PROJECTION_CENTER * (width / 2 - marge);
}

void letter_translate(Letter *letter, Vector3d vector)
{
    for (size_t i = 0; i < letter->pointsNumber; i++) {
        letter->points[i].x += vector.x;
        letter->points[i].y += vector.y;
        letter->points[i].z += vector.z;

        if (letter->points[i].z < 0) {
            fprintf(stdout, "Warning: a letter is crossing the screen !\n");
        }
    }
}

void scale(Letter *letter, float coeff)
{
    for (int i = 0; i < letter->pointsNumber; i++) {
        letter->points[i].x *= coeff;
        letter->points[i].y *= coeff;
        letter->points[i].z *= coeff;
    }
}

/**
 * \fn CvPoint3D32f barycentre(Lettre lettre)
 * \brief Calcul le barycentre d'une lettre
 *
 * \param lettre Lettre dont il faut calculter le barycentre
 *
 * \return Barycentre (point de l'espace 3d)
 */
Vector3d barycentre(Letter lettre)
{
    int i;
    Vector3d barycentre = {0, 0, 0};

    for (i = 0; i < lettre.pointsNumber; i++) {
        barycentre.x += lettre.points[i].x;
        barycentre.y += lettre.points[i].y;
        barycentre.z += lettre.points[i].z;
    }

    barycentre.x /= lettre.pointsNumber;
    barycentre.y /= lettre.pointsNumber;
    barycentre.z /= lettre.pointsNumber;

    return barycentre;
}

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

void letter_rotate(Letter *letter, Vector3d angles)
{
    Vector3d rotx[3] = {{1, 0, 0}, {0, cos(angles.x), -sin(angles.x)}, {0, sin(angles.x), cos(angles.x)}} ;
    Vector3d roty[3] = {{cos(angles.y), 0, sin(angles.y)}, {0, 1, 0}, { -sin(angles.y), 0, cos(angles.y)}} ;
    Vector3d rotz[3] = {{cos(angles.z), -sin(angles.z), 0}, {sin(angles.z), cos(angles.z), 0}, {0, 0, 1}} ;

    for (int i = 0; i < letter->pointsNumber; i++) {
        letter->points[i] = letter_apply_matrix(rotx, letter->points[i]) ;
        letter->points[i] = letter_apply_matrix(roty, letter->points[i]) ;
        letter->points[i] = letter_apply_matrix(rotz, letter->points[i]) ;
    }
}

Vector3d letter_apply_matrix(Vector3d m[3], Vector3d q)
{
    Vector3d p = {
        p.x = m[0].x * q.x + m[1].x * q.y + m[2].x * q.z ,
        p.y = m[0].y * q.x + m[1].y * q.y + m[2].y * q.z ,
        p.z = m[0].z * q.x + m[1].z * q.y + m[2].z * q.z
    };

    return p;
}
