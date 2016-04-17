#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "data.h"
#include "illumination.h"

#define max(a,b) (a>=b?a:b)

static float intensite(Light lumiere, Material materiau, Vector3d normale);

struct captcha3d_color randomColor()
{
    struct captcha3d_color couleur;

    couleur.red = rand() % 256;
    couleur.green = rand() % 256;
    couleur.blue = rand() % 256;
    couleur.alpha = 255;

    return couleur;
}

/**
 * \fn CvScalar couleurAffichageGouraud(float coeff, CvScalar couleur)
 * \brief Calcul de la couleur en fonction de la lumière pour le modèle de Gouraud
 *
 * \param coeff Multiplicateur
 * \param couleur Couleur initiale
 * \return Couleur pour Gouraud
 */
struct captcha3d_color couleurAffichageGouraud(float coeff, struct captcha3d_color couleur)
{
    couleur.red = coeff * couleur.red <= 255 ? coeff * couleur.red : 255;
    couleur.green = coeff * couleur.green <= 255 ? coeff * couleur.green : 255;
    couleur.blue = coeff * couleur.blue <= 255 ? coeff * couleur.blue : 255;

    return couleur;
}

/**
 * \fn CvScalar couleurAffichage(Face face, Materiau materiau, Lumiere lumiere,Lettre lettre)
 * \brief Calcul de la couleur d'une face
 *
 * \param face Face en cours de la lettre
 * \param materiau Matériau de la lettre
 * \param lumiere Lumière de l'environnement
 * \param lettre Lettre en cours
 * \return Couleur pour Gouraud
 */
struct captcha3d_color couleurAffichage(const Triangle *face, Material materiau, Light lumiere, const Letter *letter)
{
    struct captcha3d_color color;
    float coeff;
    Vector3d normale = face_normal_vector(face, letter->points);
    coeff = intensite(lumiere, materiau, normale);

    color.red = coeff * materiau.couleur.red <= 255 ? coeff * materiau.couleur.red : 255;
    color.green = coeff * materiau.couleur.green <= 255 ? coeff * materiau.couleur.green : 255;
    color.blue = coeff * materiau.couleur.blue <= 255 ? coeff * materiau.couleur.blue : 255;

    return color;
}

void compute_light_intensity(float tab[], Vector3d normales[], const Letter *letter, Light lumiere, Material material)
{
    Vector3d lux = normalize(&lumiere.direction);
    float angleDiffus;

    for (size_t i = 0; i < letter->pointsNumber; i++) {
        angleDiffus = max(0, angleDiffusion(lux, normales[i]));
        tab[i] = ((lumiere.ia) * (material.ka) + (lumiere.ip) * (material.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));
    }
}

/**
 * \fn float intensite(Lettre lettre, Lumiere lumiere, Materiau materiau,Vecteur normale)
 * \brief Calcul des intensités d'une lettre
 *
 * \param lettre Lettre en cours
 * \param lumiere Lumière de l'environnement
 * \param materiau Matériau de la lettre
 * \param normale Vecteur normal
 */
float intensite(Light lumiere, Material materiau, Vector3d normale)
{
    Vector3d lux = normalize(&lumiere.direction);
    float angleDiffus;

    //Calcul de l'intensité à chaque point de la lettre
    angleDiffus = max(0, angleDiffusion(lux, normale));
    return ((lumiere.ia) * (materiau.ka) + (lumiere.ip) * (materiau.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));

}

/**
 * \fn Vecteur normaleFace(Face face,CvPoint3D32f points[])
 * \brief Calcul du vecteur normale à une face
 *
 * \param face Face en cours
 * \param points[] Tableau de points
 * \return Vecteur normal
 */
Vector3d face_normal_vector(const Triangle *face, const Vector3d points[])
{
    Vector3d n;

    const Vector3d *p1 = &points[face->a];
    const Vector3d *p2 = &points[face->b];
    const Vector3d *p3 = &points[face->c];

    //Calcul du produit vectoriel pour avoir la normale
    n.x = -((p2->y - p1->y) * (p3->z - p1->z) - (p2->z - p1->z) * (p3->y - p1->y));
    n.y = -((p2->z - p1->z) * (p3->x - p1->x) - (p2->x - p1->x) * (p3->z - p1->z));
    n.z = -((p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x));

    return normalize(&n);
}

/**
 * \fn float angleDiffusion(Vecteur L, Vecteur N)
 * \brief Calcul de l'angle de diffusion
 *
 * \param L Vecteur lumière
 * \param N Vecteur normal
 * \return angle
 */
float angleDiffusion(Vector3d L, Vector3d N)
{
    //Produit scalaire pour obtenir l'angle
    return -((L.x) * (N.x) + (L.y) * (N.y) + (L.z) * (N.z));
}

/**
 * \fn void normalesAuxPoints(Vecteur tab[],Lettre lettre)
 * \brief Fonction qui calcule les normales à chaque points de la lettre
 *
 * \param tab Tableau qui recevra les normales
 * \param lettre Lettre pour laquelle il faut calculer les normales
 */
void compute_normal_vectors(Vector3d tab[], const Letter *letter)
{
    Triangle face;
    initialiserTableauNormales(tab, letter->pointsNumber);

    for (size_t i = 0; i < letter->facesNumber; i++) {
        face = letter->faces[i];

        Vector3d normal = face_normal_vector(&letter->faces[i], letter->points);

        tab[face.a] = vector_add(&tab[face.a], &normal);
        tab[face.b] = vector_add(&tab[face.b], &normal);
        tab[face.c] = vector_add(&tab[face.c], &normal);
    }

    for (size_t i = 0; i < letter->pointsNumber; i++) {
        tab[i] = normalize(&tab[i]);
    }
}

/**
 * \fn void initialiserTableauNormales(Vecteur tab[],int taille)
 * \brief Initialise un tableau avec la normale nulle
 *
 * \param tab Tableau à initialiser
 * \param taille Taille du tableau
 */
void initialiserTableauNormales(Vector3d tab[], int taille)
{
    Vector3d nul;
    int i;

    nul.x = 0;
    nul.y = 0;
    nul.z = 0;

    for (i = 0; i < taille; i++) {
        tab[i] = nul;
    }
}

