#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <math.h>

#include "data.h"
#include "transformations.h"

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
    *e = (float) (Z_CENTRE_PROJECTION + (*z)) / Z_CENTRE_PROJECTION * height * 0.8 / 2. / 6.;
    //Offset entre chaque lettre
    *offset = (float) ((width - 2 * (*marge)) / (nbLettres - 1)) * (Z_CENTRE_PROJECTION + fabs(*z)) / Z_CENTRE_PROJECTION;
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
Letter transformation(Letter lettre, int i, int width, int height, int z, int marge, float e, float offset)
{
    Vector3d translate;
    float angle1, angle2, angle3;

//    // Déformation
//    if (cfg_deform_sin) {
//        lettre = deformation_sin(lettre, 'h');
//    }

    // Mise à l'échelle de la lettre
    lettre = echelle(lettre, e) ;

    // Rotation de la lettre
    angle1 = (float) 1.5 * rand() / RAND_MAX - 0.75;
    angle2 = (float) 1.5 * rand() / RAND_MAX - 0.75;
    angle3 = (float) 1.5 * rand() / RAND_MAX - 0.75;

    //Rotation aléatoire
    Vector3d angles = {angle1, angle2, angle3} ;
    lettre = rotation(lettre, angles);

    // Translation de la lettre
    translate = calculterTranslation(width, height, marge, z);

    //On décale la lettre de i fois le offset
    translate.x += offset * i;
    lettre = translation(lettre, translate);

    return lettre;
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
    return (float) width / 2 - (fabs(z) + Z_CENTRE_PROJECTION) / Z_CENTRE_PROJECTION * (width / 2 - marge);

}

/**
 * \fn Lettre translation(Lettre lettre,Vecteur vecteur)
 * \brief Translate une lettre dans l'espace
 *
 * \param lettre Lettre à translater
 * \param vecteur Vecteur de translation
 *
 * \return Lettre translatée
 */
Letter translation(Letter lettre, Vector3d vecteur)
{
    Letter lettreTranslatee = lettre;
    int i;
    for (i = 0; i < lettre.numPoints; i++) {
        lettreTranslatee.points[i].x += vecteur.x;
        lettreTranslatee.points[i].y += vecteur.y;
        lettreTranslatee.points[i].z += vecteur.z;
        if (lettreTranslatee.points[i].z < 0) {
            fprintf(stdout, "\n*********************\nTraversée de l'écran !\n*********************\n\n");
        }
    }

    return lettreTranslatee;
}

/**
 * \fn Lettre echelle(Lettre lettre, float coeff)
 * \brief Modifie les dimensions d'une lettre suivant un facteur coeef
 *
 * \param lettre Lettre dont il faut modifier les dimensions
 * \param coeff Coefficient de multiplication des dimensions
 *
 * \return Lettre mise à l'échelle
 */
Letter echelle(Letter lettre, float coeff)
{
    Letter lettreRedimensionnee = lettre;
    int i;
    for (i = 0; i < lettre.numPoints; i++) {
        lettreRedimensionnee.points[i].x *= coeff;
        lettreRedimensionnee.points[i].y *= coeff;
        lettreRedimensionnee.points[i].z *= coeff;
    }

    return lettreRedimensionnee;
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

    for (i = 0; i < lettre.numPoints; i++) {
        barycentre.x += lettre.points[i].x;
        barycentre.y += lettre.points[i].y;
        barycentre.z += lettre.points[i].z;
    }

    barycentre.x /= lettre.numPoints;
    barycentre.y /= lettre.numPoints;
    barycentre.z /= lettre.numPoints;

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

    for (i = 0; i < lettre.numPoints; i++) {
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

    for (i = 0; i < lettre.numPoints; i++) {
        p = lettre.points[i];

        if (type == 'v') {
            p.y += DEFORMATION_SIN_AMPLITUDE * sin((2 * PI) / DEFORMATION_SIN_PERIODE * p.x);
        } else {
            p.x += DEFORMATION_SIN_AMPLITUDE * sin((2 * PI) / DEFORMATION_SIN_PERIODE * p.y);
        }

        lettre.points[i] = p;
    }

    return lettre;
}

/**
 * \fn Lettre rotation(Lettre lettre,Vecteur angles)
 * \brief Rotation sur les 3 axes d'une lettre
 *
 * \param lettre Lettre sur laquelle on applique la rotation
 * \param angles Vecteur contenant les 3 angles selon x, y et z
 *
 * \return 	Lettre ayant subie la rotation
 */
Letter rotation(Letter lettre, Vector3d angles)
{
    Letter lettreRot = lettre;

    // Initialisation des matrices
    Vector3d rotx[3] = {{1, 0, 0}, {0, cos(angles.x), -sin(angles.x)}, {0, sin(angles.x), cos(angles.x)}} ;
    Vector3d roty[3] = {{cos(angles.y), 0, sin(angles.y)}, {0, 1, 0}, { -sin(angles.y), 0, cos(angles.y)}} ;
    Vector3d rotz[3] = {{cos(angles.z), -sin(angles.z), 0}, {sin(angles.z), cos(angles.z), 0}, {0, 0, 1}} ;

    int i;
    for (i = 0; i < lettre.numPoints; i++) {
        // Rotation sur x
        lettreRot.points[i] = appliquerMatrice(rotx, lettreRot.points[i]) ;

        // Rotation sur y
        lettreRot.points[i] = appliquerMatrice(roty, lettreRot.points[i]) ;

        // Rotation sur z
        lettreRot.points[i] = appliquerMatrice(rotz, lettreRot.points[i]) ;
    }

    return lettreRot;
}

/**
 * \fn Vecteur appliquerMatrice(Vecteur m[3], Vecteur q)
 * \brief Fonction qui calcule l'image d'un vecteur par une matrice
 *
 * \param m[3]	Matrice à appliquer
 * \param q Vecteur sur lequel on applique la matrice
 *
 * \return 	Point 3d
 */
Vector3d appliquerMatrice(Vector3d m[3], Vector3d q)
{
    Vector3d p = {
        p.x = m[0].x * q.x + m[1].x * q.y + m[2].x * q.z ,
        p.y = m[0].y * q.x + m[1].y * q.y + m[2].y * q.z ,
        p.z = m[0].z * q.x + m[1].z * q.y + m[2].z * q.z
    } ;
    return p ;
}
